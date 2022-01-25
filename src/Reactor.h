#ifndef __REACTOR_H__
#define __REACTOR_H__

#include <zmq.hpp>
#include <string>
#include <thread>
#include "EventService.h"

namespace reactor {
    /**
     * @brief The main reactor class
     * 
     * The reactor class can both send and receive messages. The messages are processed
     * here to know what to do with the messages. This is an abstract class so that
     * the implementation of what to do with a consumed message is done.
     * 
     */
    class Reactor {

        public:
            /**
             * @brief The type of socket for this class
             * 
             * This will be a dealer socket
             * 
             */
            zmq::socket_type socketType;
            /**
             * @brief The reactor id
             * 
             * This is how this reactor identifies itself. This integer should
             * be available to others to know how to pass messages to it.
             */
            int rid;

            /**
             * @brief Construct a new Reactor object.
             * 
             * @param p_reactorId The reactor's id or way to identify themselves
             */
            Reactor(int p_reactorId);

            /**
             * @brief Construct a new Reactor object
             * 
             * @param p_reactorId The reactor's id or way to identify themselves
             * @param p_socketAddr The socket's custom address
             */
            Reactor(int p_reactorId, std::string p_socketAddr);

            /**
             * @brief Destroy the Reactor object
             * 
             * Since this is an abstract class the destructor does not call thread.join()
             * here. It is highly advised that the derived class does.
             */
            virtual ~Reactor();

            /**
             * @brief Send a message to a reactor
             * 
             * Sends a string to the reactor. The string could be a normal string
             * or a protocol buffer object to be able to send an actual object
             * to a reactor.
             * 
             * @param p_destReactorId The reactor id to send to
             * @param p_message The message to send to the reactor
             */
            void sendMessage(int p_destReactorId, std::string p_message);

            /**
             * @brief Starts the object's thread
             * 
             * The constructing of the object starts in the main thread and then the actual
             * operation of the object needs to be started seperately.
             */
            void start();

        protected:
            /**
             * @brief The thread
             * 
             */
            std::thread thread_object;
        
        private:
            /**
             * @brief The zmq context
             * 
             */
            zmq::context_t context;

            /**
             * @brief The dealer socket
             * 
             */
            zmq::socket_t* dealerSocket;

            /**
             * @brief Keeps the thread running
             * 
             */
            bool isRunning = true;

            /**
             * @brief The default socket address
             * 
             */
            std::string socketAddress = "tcp://127.0.0.1:5555";

            /**
             * @brief How the actual class runs in the thread
             * 
             * This gets called by start()
             */
            void run();

            /**
             * @brief Stops the thread by stopping the run method, closes the socket
             * and then the object will come to the end of its lifetime
             * 
             */
            void stopThread();

            /**
             * @brief How to this reactor will consume the message
             * 
             * Defines on how the current reactor will consume the messages coming in. This is
             * where the real power comes from.
             */
            virtual void consumeMsg(std::string) = 0;

            /**
             * @brief Process the fail message. Up to the user on what to do with the message
             * 
             */
            virtual void processFailMsg(std::string, int) = 0;

    };
}

#endif // __REACTOR_H__