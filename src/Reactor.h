#ifndef __REACTOR_H__
#define __REACTOR_H__

#include <string>
#include <thread>

/**
 * @brief Forward declare library
 * 
 */
namespace zmq {
    class context_t;
    class socket_t;
}

namespace reactor {
    /**
     * @brief The main reactor class.
     * The reactor class can both send and receive messages. The messages are processed
     * here to know what to do with the messages. This is an abstract class so that
     * the implementation of what to do with a consumed message is done.
     */
    class Reactor {

        public:
            /**
             * @brief The reactor id.
             * This is how this reactor identifies itself. This integer should
             * be available to others to know how to pass messages to it.
             */
            int reactorId;

            /**
             * @brief Construct a new Reactor object.
             * 
             * @param p_reactorId The reactor's id or way to identify themselves
             */
            Reactor(int p_reactorId);

            /**
             * @brief Construct a new Reactor object.
             * 
             * @param p_reactorId The reactor's id or way to identify themselves
             * @param p_socketAddress The socket's custom address
             */
            Reactor(int p_reactorId, std::string p_socketAddress);

            /**
             * @brief Destroy the Reactor object.
             * Since this is an abstract class the destructor does not call thread.join()
             * here. It is highly advised that the derived class does.
             */
            virtual ~Reactor();

            /**
             * @brief Send a message to a reactor.
             * Sends a character pointer to the reactor and the size of the
             * object you would like to send
             * 
             * @param p_destReactorId The reactor id to send to
             * @param p_message The message to send to the reactor
             */
            void sendMessage(int p_destReactorId, const std::string& p_message);

            /**
             * @brief Start the Reactor by connecting the socket to the address and
             * then starting the thread.
             */
            void start();

        protected:
            /**
             * @brief The thread object.
             */
            std::thread thread_object;

            /**
             * @brief Resends a message back to a given reactor with the number of attempts
             * to keep track how many times the reactor has attempted to send a message. The
             * number of attempts should be passed from the processFailMessage function only.
             * The number of attempts is to help not overflow any queues and not overload
             * the network traffic.
             * 
             * @param p_destRid The ID of the reactor to send the message to
             * @param p_numOfAttempts The number of attempts this mesage has been sent but failed to deliver
             * @param p_message The message itself
             */
            void resendMessage(int p_destRid, int p_numOfAttempts, std::string p_message);
        
        private:

            /**
             * @brief The dealer socket.
             */
            zmq::socket_t* dealerSocket;

            /**
             * @brief The ZMQ context
             * 
             */
            zmq::context_t* context;

            /**
             * @brief A boolean to see if the class should keep going or shut down.
             */
            bool isRunning = true;

            /**
             * @brief The default address that the socket should connect to.
             */
            std::string socketAddress = "tcp://127.0.0.1:5555";

            /**
             * @brief The method that actually runs to send and receive messages.
             */
            void run();

            /**
             * @brief Stops the thread by stopping the run method, closes the socket
             * and then the object will come to the end of its lifetime.
             */
            void stopThread();

            /**
             * @brief How to this reactor will consume the message.
             * Defines on how the current reactor will consume the messages coming in. This is
             * where the real power comes from.
             * 
             * @param p_message The message that was sent
             */
            virtual void consumeMessage(std::string p_message) = 0;

            /**
             * @brief Process the fail message. Up to the user on what to do with the message.
             * 
             * @param p_destRid The ID of the reactor where the message was supposed to go
             * @param p_failMsgStr The FAIL_TO_DELIVER string
             * @param p_message The message that was supposed to send
             * @param p_numOfAttempts The number of attempts that the message has tried to send to the reactor
             */
            virtual void processFailMessage(int p_destRid, std::string p_failMsgStr, std::string p_message, int p_numOfAttempts) = 0;

    };
}

#endif // __REACTOR_H__