#ifndef __EVENTSERVICE_H__
#define __EVENTSERVICE_H__

#include <map>
#include <zmq.hpp>
#include <vector>
#include <thread>
#include <string>

namespace reactor {
    /**
     * @brief The router to route messages for reactors
     * 
     * The event service is a service that acts as a router to route messages
     * for the reactor. When a reactor wants to send to a specific reactor the
     * event service will accept the message and try to deliver the message.
     * 
     */
    class EventService {

        public:
            /**
             * @brief The type of socket for this class
             * 
             * This will be a router socket
             * 
             */
            zmq::socket_type socketType;
            /**
             * @brief Whether or not the event service is ready
             * 
             */
            bool isReady;


            /**
             * @brief Construct a new Event Service object
             * 
             * Starts the event service object by binding to the address.
             */
            EventService();
            /**
             * @brief Construct a new Event Service object
             * 
             * @param p_socketAddr The custom address for the socket
             */
            EventService(std::string p_socketAddr);
            /**
             * @brief Destroy the Event Service object
             * 
             * Joins the thread and destroys the object.
             * 
             */
            ~EventService();
            /**
             * @brief Starts the thread
             * 
             * This is needed to be able to route the messages.
             * 
             */
            void start();

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
            zmq::socket_t* routerSocket;
            /**
             * @brief The thread
             * 
             */
            std::thread thread_object;

            /**
             * @brief How the actual thread runs
             * 
             * This gets called by start()
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
             * @brief Send a fail message back to the router
             * 
             */
            void sendFailMsg(zmq::message_t* p_sourceMsg);
    };
}

#endif // __EVENTSERVICE_H__