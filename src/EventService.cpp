#include <thread>
#include <iterator>
#include <map>
#include <vector>
#include <string>

#include "zmq.hpp"
#include "spdlog/spdlog.h"
#include "EventService.h"
#include "event_message_types.h"
#include "ReactorId.h"
#include "MsgAttempts.h"

namespace reactor {

    EventService::EventService() {

        context = new zmq::context_t();

        // Setup a router socket
        routerSocket = new zmq::socket_t(*context, zmq::socket_type::router);
        routerSocket->setsockopt(ZMQ_ROUTER_MANDATORY, 1);

        routerSocket->bind(socketAddress);
               
    }

    EventService::EventService(std::string p_socketAddress) : socketAddress(p_socketAddress) {

        context = new zmq::context_t();

        // Setup a router socket
        routerSocket = new zmq::socket_t(*context, zmq::socket_type::router);
        routerSocket->setsockopt(ZMQ_ROUTER_MANDATORY, 1);

        routerSocket->bind(p_socketAddress);

    }

    void EventService::run(void) {

        zmq::recv_result_t recv;

        /**
         * @brief Receive messages and then pass them
         */
        while(isRunning) {
            // Where it came from (the dealer who sent it, it's id)
            zmq::message_t sourceMsg;
            // Where it is supposed to (the dealer to send to)
            zmq::message_t destMsg;
            // The number of attempts for the message being sent
            zmq::message_t numOfAttemptsMsg;
            // The actual message that needs to be sent (this could be anything)
            zmq::message_t msg;

            // Get the actual message
            recv = routerSocket->recv(sourceMsg, zmq::recv_flags::dontwait);
            if(sourceMsg.empty()) {
                continue;
            }

            recv = routerSocket->recv(destMsg, zmq::recv_flags::none);

            recv = routerSocket->recv(numOfAttemptsMsg, zmq::recv_flags::none);

            recv = routerSocket->recv(msg, zmq::recv_flags::none);

            try {
                passMessage(&destMsg, &msg);
            } catch(const zmq::error_t error) {
                #ifdef ENABLE_ROUTER_ERROR

                reactor::ReactorId sourceId;
                reactor::ReactorId destId;

                std::string sourceMsgStr (static_cast<char *>(sourceMsg.data())); 
                sourceId.ParseFromArray(sourceMsg.data(), sourceMsgStr.length());

                std::string destMsgStr (static_cast<char *>(destMsg.data()));
                destId.ParseFromArray(destMsg.data(), destMsgStr.length());

                spdlog::error("ZMQ ERROR: {} :: Source {} :: Destination {}", error.what(), sourceId.reactorid(), destId.reactorid());
                #endif
                sendFailMsg(&sourceMsg, &destMsg, &numOfAttemptsMsg, &msg);
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

        routerSocket->send(*p_destMsg, zmq::send_flags::sndmore);
        routerSocket->send(*p_message, zmq::send_flags::none);

    }

    void EventService::sendFailMsg(zmq::message_t* p_sourceMsg, zmq::message_t* p_destMsg, zmq::message_t* p_numOfAttempts, zmq::message_t* p_message) {
        
        reactor::MsgAttempts messageAttempts;
        std::string messageAttemptsStr (static_cast<char *>(p_numOfAttempts->data()));
        std::size_t messageAttemptsSize = messageAttemptsStr.length();

        messageAttempts.ParseFromArray(p_numOfAttempts->data(), messageAttemptsSize);
        int32_t currentAttempts = messageAttempts.numofattempts();
        currentAttempts = currentAttempts + 1;

        messageAttempts.set_numofattempts(currentAttempts);
        messageAttemptsSize = messageAttempts.ByteSizeLong();

        char* messageAttemptsArray = new char[messageAttemptsSize];
        messageAttempts.SerializePartialToArray(messageAttemptsArray, messageAttemptsSize);

        zmq::message_t numOfAttemptsMsg (messageAttemptsArray, messageAttemptsSize);
        
        zmq::message_t failMsg (reactor::type::FAIL_TO_DELIVER);

        routerSocket->send(*p_sourceMsg, zmq::send_flags::sndmore);
        routerSocket->send(failMsg, zmq::send_flags::sndmore);
        routerSocket->send(*p_destMsg, zmq::send_flags::sndmore);
        routerSocket->send(numOfAttemptsMsg, zmq::send_flags::sndmore);
        routerSocket->send(*p_message, zmq::send_flags::none);

    }
}