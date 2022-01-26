#ifndef __EVENTSERVICE_H__
#define __EVENTSERVICE_H__

#include <map>
#include <vector>
#include <thread>
#include <string>

//#include "zmq.hpp"

/**
 * @author Kyle Gagnon
 * @date 01/25/2021
 */
namespace reactor {
    /**
     * @brief The router to route messages for reactors.
     * The event service is a service that acts as a router to route messages
     * for the reactor. When a reactor wants to send to a specific reactor the
     * event service will accept the message and try to deliver the message.
     */
    class EventService {

        public:
            /**
             * @brief The type of socket for this class
             */
            zmq::socket_type routerSocketType = zmq::socket_type::router;

            /**
             * @brief Construct a new Event Service object.
             * 
             * Starts the event service object by binding to the address.
             */
            EventService();

            /**
             * @brief Construct a new Event Service object.
             * 
             * @param p_socketAddress The custom address for the socket
             */
            EventService(std::string p_socketAddress);

            /**
             * @brief Destroy the Event Service object by joining the thread and closing the socket.
             */
            ~EventService();

            /**
             * @brief Start the event service by binding the socket to the address. After that it starts
             * the thread.
             */
            void start();

        private:
            /**
             * @brief The ZMQ context.
             */
            zmq::context_t context;

            /**
             * @brief The actual router socket.
             */
            zmq::socket_t* routerSocket;

            /**
             * @brief The thread object.
             */
            std::thread thread_object;

            /**
             * @brief The default address the router socket will bind to.
             */
            std::string socketAddress = "tcp://127.0.0.1:5555";

            /**
             * @brief The actual actions that happens when the thread starts.
             */
            void run();

            /**
             * @brief Attempt to deliver the given message.
             * 
             * @param p_destination The zmq message of the destination
             * @param p_message This is the acutal message to send over
             */
            void passMessage(zmq::message_t* p_destination, zmq::message_t* p_message);

            /**
             * @brief Sends a message back to the router stating a failure in sending
             * 
             * @param p_sourceMsg The source of where it came from
             * @param p_destMsg The destination of where it was sending to
             */
            void sendFailMsg(zmq::message_t* p_sourceMsg, zmq::message_t* p_destMsg);
    };
}

#endif // __EVENTSERVICE_H__