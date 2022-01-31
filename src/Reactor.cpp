#include <thread>
#include <sstream>
#include <iomanip>

#include "spdlog/spdlog.h"
#include "zmq.hpp"
#include "Reactor.h"
#include "ReactorId.h"
#include "event_message_types.h"
#include "MsgAttempts.h"

namespace reactor {
    Reactor::Reactor(int p_reactorId) : reactorId(p_reactorId) {

        context = new zmq::context_t();

        /*
        * Default Constructor
        */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with reactorId of {}", reactorId);
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
        reactorIdStruct.set_reactorid(reactorId);
        std::size_t structSize = reactorIdStruct.ByteSizeLong();

        char* reactorIdArray = new char[structSize];
        reactorIdStruct.SerializeToArray((void *)reactorIdArray, structSize);
        /*
         * End of creating a ReactorId object
         */

        dealerSocket = new zmq::socket_t(*context, zmq::socket_type::dealer);

        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)reactorIdArray, structSize);
        dealerSocket->connect(socketAddress);

    }

    Reactor::Reactor(int p_reactorId, std::string p_socketAddress) : reactorId(p_reactorId), socketAddress(p_socketAddress) {

        context = new zmq::context_t();

        /**
         * @brief Constructor to include a custom address for the socket
         * 
         */
        #ifdef DEBUG_OUTPUT
        spdlog::debug("Starting Reactor constructor with reactorId of {}", reactorId);
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
        reactorIdStruct.set_reactorid(reactorId);
        std::size_t structSize = reactorIdStruct.ByteSizeLong();

        char* reactorIdArray = new char[structSize];
        reactorIdStruct.SerializeToArray((void *)reactorIdArray, structSize);
        /*
         * End of creating a ReactorId object
         */
        dealerSocket = new zmq::socket_t(*context, zmq::socket_type::dealer);

        dealerSocket->setsockopt(ZMQ_ROUTING_ID, (void *)reactorIdArray, structSize);
        dealerSocket->connect(p_socketAddress);

    }

    void Reactor::run() {

        zmq::message_t msg;
        zmq::message_t destMsg;
        zmq::message_t numOfAttemptsMsg;
        zmq::message_t originalMsg;
        zmq::recv_result_t recv;

        while(isRunning) {
            // Get the actual message
            recv = dealerSocket->recv(msg, zmq::recv_flags::dontwait);
            if(msg.empty()) {
                continue;
            }

            if(msg.to_string() == reactor::type::FAIL_TO_DELIVER) {
                recv = dealerSocket->recv(destMsg, zmq::recv_flags::none);
                recv = dealerSocket->recv(numOfAttemptsMsg, zmq::recv_flags::none);
                recv = dealerSocket->recv(originalMsg, zmq::recv_flags::none);

                reactor::ReactorId destId;
                std::string destMsgStr (static_cast<char *>(destMsg.data()));
                destId.ParseFromArray(destMsg.data(), destMsgStr.length());

                reactor::MsgAttempts numOfAttemps;
                std::string numOfAttemptsStr (static_cast<char *>(numOfAttemptsMsg.data()));
                numOfAttemps.ParseFromArray(numOfAttemptsMsg.data(), numOfAttemptsStr.length());

                std::string messageStr (static_cast<char *>(originalMsg.data()));

                processFailMessage(destId.reactorid(), msg.to_string(), messageStr, numOfAttemps.numofattempts());
            } else {
                consumeMessage(msg.to_string());
            } 
        }
    }

    void Reactor::sendMessage(int p_destRid, const std::string& p_message) {

        /*
         * Convert destination reactorId (int) to ReactorId object
         */
        reactor::ReactorId destReactorId;
        destReactorId.set_reactorid(p_destRid);
        std::size_t structSize = destReactorId.ByteSizeLong();

        char* destReactorIdArray = new char[structSize];
        destReactorId.SerializeToArray((void *)destReactorIdArray, structSize);

        reactor::MsgAttempts messageAttempts;
        messageAttempts.set_numofattempts(0);
        std::size_t messageAttemptsSize = messageAttempts.ByteSizeLong();

        char* messageAttemptsArray = new char[messageAttemptsSize];
        messageAttempts.SerializeToArray((void *)messageAttemptsArray, messageAttemptsSize);

        zmq::message_t destRid (destReactorIdArray, structSize);
        dealerSocket->send(destRid, zmq::send_flags::sndmore);

        zmq::message_t numOfAttempts (messageAttemptsArray, messageAttemptsSize);
        dealerSocket->send(numOfAttempts, zmq::send_flags::sndmore);

        zmq::message_t message (p_message);
        dealerSocket->send(message, zmq::send_flags::none);

    }

    void Reactor::resendMessage(int p_destRid, int p_numOfAttempts, std::string p_message) {

        /*
         * Convert destination reactorId (int) to ReactorId object
         */
        reactor::ReactorId destReactorId;
        destReactorId.set_reactorid(p_destRid);
        std::size_t destReactorIdSize = destReactorId.ByteSizeLong();

        reactor::MsgAttempts numOfAttempts;
        numOfAttempts.set_numofattempts(p_numOfAttempts);
        std::size_t numOfAttemptsSize = numOfAttempts.ByteSizeLong();

        char* destReactorIdArray = new char[destReactorIdSize];
        destReactorId.SerializeToArray((void *)destReactorIdArray, destReactorIdSize);

        char* numOfAttemptsArray = new char[numOfAttemptsSize];
        numOfAttempts.SerializeToArray((void *)numOfAttemptsArray, numOfAttemptsSize);

        zmq::message_t destRidMsg (destReactorIdArray, destReactorIdSize);
        zmq::message_t numOfAttemptsMsg (numOfAttemptsArray, numOfAttemptsSize);
        zmq::message_t originalMsg (p_message);

        dealerSocket->send(destRidMsg, zmq::send_flags::sndmore);
        dealerSocket->send(numOfAttemptsMsg, zmq::send_flags::sndmore);
        dealerSocket->send(originalMsg, zmq::send_flags::none);

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