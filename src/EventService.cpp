#include <thread>
#include <zmq.hpp>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include "spdlog/spdlog.h"
#include "EventService.h"
#include "event_message_types.h"

namespace reactor {

    EventService::EventService() {

        // Setup a router socket
        socketType = zmq::socket_type::router;
        routerSocket = new zmq::socket_t(context, socketType);
        routerSocket->setsockopt(ZMQ_ROUTER_MANDATORY, 1);

        do
        {
            routerSocket->bind("ipc://eventServiceIpc.ipc");
        } while (!(routerSocket->connected()));

        isReady = true;
        
        
    }

    EventService::EventService(std::string p_socketAddr) {

        // Setup a router socket
        socketType = zmq::socket_type::router;
        routerSocket = new zmq::socket_t(context, socketType);
        routerSocket->setsockopt(ZMQ_ROUTER_MANDATORY, 1);

        do
        {
            routerSocket->bind(p_socketAddr);
        } while (!(routerSocket->connected()));

        isReady = true;

    }

    void EventService::run(void) {

        zmq::recv_result_t recv;

        /**
         * @brief Receive messages and then pass them
         */
        while(1) {
            // Where it came from (the dealer who sent it, it's id)
            zmq::message_t sourceMsg;
            // Where it is supposed to (the dealer to send to)
            zmq::message_t destMsg;
            // The actual message that needs to be sent (this could be anything)
            zmq::message_t msg;

            /**
             * @brief How messages are processed
             * 
             * To be able to do any messaging we need this event service class. This event service class is the way to pass messages from one dealer to another.
             * This class is mainly used to just route messages.
             * 
             * Any message can be received at any time. There are two main messages. A STARTUP message when a dealer (reactor) comes online and anything else.
             * All reactors and anything that wants to send to the router must send a multi message of 4 messages (usually just using the sndmore flag rather than
             * an actual multi message).
             * 
             * First Message: Where it came from - This is the id of socket of the dealer that sent this message.
             * Second Message: Where it is going to
             * Third Message: Used to identify what event this is. This helps the router decide what to parse the message to (what event) and what to do with it
             * Fourth Message: The actual message. We don't really need to know what this message is if it isn't a STARTUP message
             * 
             */

            // Get the actual message
            recv = routerSocket->recv(sourceMsg, zmq::recv_flags::dontwait);
            if(sourceMsg.empty()) {
                continue;
            }

            #ifdef DEBUG_ROUTER_RECV
            spdlog::debug("Source As To Int: {}", sourceId);
            #endif

            recv = routerSocket->recv(destMsg, zmq::recv_flags::none);

            #ifdef DEBUG_ROUTER_RECV
            spdlog::debug("Destination or ID: {}", destId);
            #endif

            recv = routerSocket->recv(msg, zmq::recv_flags::none);

            #ifdef DEBUG_ROUTER_RECV
            spdlog::debug("Message: {}", msg.str());
            #endif

            try {
                passMessage(&destMsg, &msg);
            } catch(const zmq::error_t error) {
                #ifdef ENABLE_ROUTER_ERROR
                int source = *(static_cast<int *>(sourceMsg.data()));
                int destination = *(static_cast<int *>(destMsg.data()));
                spdlog::error("ZMQ ERROR: {} :: Source {} :: Destination {}", error.what(), source, destination);
                #endif
                sendFailMsg(&sourceMsg, &destMsg);
            }
        }

        routerSocket->close();
    }

    void EventService::start() {
        thread_object = std::thread (&EventService::run, this);
    }

    EventService::~EventService() {
        thread_object.join();
    }

    void EventService::passMessage(zmq::message_t* p_destMsg, zmq::message_t* p_message) {

        zmq::message_t cpyMsg (p_message->size());
        cpyMsg.copy(*(p_message));

        routerSocket->send(*(p_destMsg), zmq::send_flags::sndmore);
        routerSocket->send(cpyMsg, zmq::send_flags::none);

    }

    void EventService::sendFailMsg(zmq::message_t* p_sourceMsg, zmq::message_t* p_destMsg) {
        
        zmq::message_t failMsg (reactor::type::FAIL_TO_DELIVER);

        routerSocket->send(*p_sourceMsg, zmq::send_flags::sndmore);
        routerSocket->send(failMsg, zmq::send_flags::sndmore);
        routerSocket->send(*p_destMsg, zmq::send_flags::none);

    }
}