#include <thread>
#include <sstream>
#include <iomanip>
#include "spdlog/spdlog.h"
#include "zmq.hpp"
#include "Reactor.h"
#include "ReactorId.h"
#include "event_message_types.h"

namespace reactor {
    Reactor::Reactor(int p_rid) : rid(p_rid) {

        /*
        * Default Constructor
        */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with RID of {}", rid);
        #endif

        /**
         * Start of creating a ReactorId object
         * 
         * The ReactorId object is used to help support the ability
         * to talk from C++ to other language bindings. This uses
         * Google's Protobuf to create a way to set a id of the
         * socket and can move it around.
         */
        reactor::ReactorId reactorIdStruct;
        reactorIdStruct.set_rid(rid);
        std::size_t structSize = reactorIdStruct.ByteSizeLong();

        char* reactorIdArray = new char[structSize];
        reactorIdStruct.SerializeToArray((void *)reactorIdArray, structSize);
        /*
         * End of creating a ReactorId object
         */

        socketType = zmq::socket_type::dealer;
        dealerSocket = new zmq::socket_t(context, socketType);

        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)reactorIdArray, structSize);
        
        try {
            dealerSocket->connect(socketAddress);
        } catch(const zmq::error_t error) {
            spdlog::error("{}", error.what());
        }

    }

    Reactor::Reactor(int p_rid, std::string p_socketAddr) : rid(p_rid) {

        /**
         * @brief Constructor to include a custom address for the socket
         * 
         */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with RID of {}", rid);
        #endif

        /**
         * Start of creating a ReactorId object
         * 
         * The ReactorId object is used to help support the ability
         * to talk from C++ to other language bindings. This uses
         * Google's Protobuf to create a way to set a id of the
         * socket and can move it around.
         */
        reactor::ReactorId reactorIdStruct;
        reactorIdStruct.set_rid(rid);
        std::size_t structSize = reactorIdStruct.ByteSizeLong();

        char* reactorIdArray = new char[structSize];
        reactorIdStruct.SerializeToArray((void *)reactorIdArray, structSize);
        /*
         * End of creating a ReactorId object
         */

        socketType = zmq::socket_type::dealer;
        dealerSocket = new zmq::socket_t(context, socketType);

        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)reactorIdArray, structSize);

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

                reactor::ReactorId destId;
                std::string destMsgStr (static_cast<char *>(destMsg.data()));
                destId.ParseFromArray(destMsg.data(), destMsgStr.length());

                processFailMsg(msg.to_string(), destId.rid());
            } else {
                consumeMsg(msg.to_string());
            } 
        }
    }

    void Reactor::sendMessage(int p_destRid, std::string p_message) {

        /*
         * Convert destination rid (int) to ReactorId object
         */
        reactor::ReactorId destReactorId;
        destReactorId.set_rid(p_destRid);
        std::size_t structSize = destReactorId.ByteSizeLong();

        char* destReactorIdArray = new char[structSize];
        destReactorId.SerializeToArray((void *)destReactorIdArray, structSize);

        zmq::message_t destRid ((void *)destReactorIdArray, structSize);
        dealerSocket->send(destRid, zmq::send_flags::sndmore);

        zmq::message_t message (p_message);
        dealerSocket->send(message, zmq::send_flags::none);

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