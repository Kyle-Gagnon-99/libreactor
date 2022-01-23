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

        dealerSocket->connect(socketAddress);

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

        try {
            dealerSocket->connect(p_socketAddr);
        } catch(const zmq::error_t error) {
            spdlog::error("{}", error.what());
        }

    }

    void Reactor::run() {

        zmq::message_t msg;
        zmq::message_t destMsg;
        zmq::recv_result_t recv;

        while(isRunning) {
            // Get the actual message
            recv = dealerSocket->recv(msg, zmq::recv_flags::dontwait);
            if(msg.empty()) {
                continue;
            }

            if(msg.to_string() == reactor::type::FAIL_TO_DELIVER) {
                recv = dealerSocket->recv(destMsg, zmq::recv_flags::none);
                int dest = *(static_cast<int *>(destMsg.data()));
                processFailMsg(msg.to_string(), dest);
            } else {
                consumeMsg(msg.to_string());
            } 
        }
    }

    void Reactor::sendMessage(int p_destRid, std::string p_evBase) {

        zmq::message_t destRid ((void *)&p_destRid, sizeof(p_destRid));
        dealerSocket->send(destRid, zmq::send_flags::sndmore);

        zmq::message_t eventMsg (p_evBase);
        dealerSocket->send(eventMsg, zmq::send_flags::none);

    }

    void Reactor::stopThread() {
        isRunning = false;
        dealerSocket->close();
    }

    void Reactor::start() {
        thread_object = std::thread(&Reactor::run, this);
    }

    Reactor::~Reactor() {
        
    }
}