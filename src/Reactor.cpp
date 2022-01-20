#include <thread>
#include "spdlog/spdlog.h"
#include "zmq.hpp"
#include "Reactor.h"
#include "event_message_types.h"

namespace reactor {
    Reactor::Reactor(int p_rid) : rid(p_rid) {

        /*
        * Default Constructor
        */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with RID of {}", rid);
        #endif

        socketType = zmq::socket_type::dealer;
        dealerSocket = new zmq::socket_t(context, socketType);
        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)&rid, sizeof(rid));

        dealerSocket->connect("ipc://eventServiceIpc.ipc");

    }

    Reactor::Reactor(int p_rid, std::string p_socketAddr) : rid(p_rid) {

        /**
         * @brief Constructor to include a custom address for the socket
         * 
         */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with RID of {}", rid);
        #endif

        socketType = zmq::socket_type::dealer;
        dealerSocket = new zmq::socket_t(context, socketType);
        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)&rid, sizeof(rid));

        dealerSocket->connect(p_socketAddr);

    }

    void Reactor::run() {

        zmq::message_t msg;
        zmq::recv_result_t recv;

        while(1) {
            // Get the actual message
            recv = dealerSocket->recv(msg, zmq::recv_flags::dontwait);
            if(msg.empty()) {
                continue;
            }
            
            consumeMsg(msg.to_string());
        }
    }

    void Reactor::sendMessage(int p_destRid, std::string p_evBase) {

        zmq::message_t destRid ((void *)&p_destRid, sizeof(p_destRid));
        dealerSocket->send(destRid, zmq::send_flags::sndmore);

        zmq::message_t eventMsg (p_evBase);
        dealerSocket->send(eventMsg, zmq::send_flags::none);

    }

    void Reactor::sendMessage(zmq::message_t* p_destMsg, zmq::message_t* p_msg) {
        
        dealerSocket->send(*(p_destMsg), zmq::send_flags::sndmore);
        dealerSocket->send(*(p_msg), zmq::send_flags::none);

    }

    void Reactor::start() {
        thread_object = std::thread(&Reactor::run, this);
    }

    Reactor::~Reactor() {

    }
}