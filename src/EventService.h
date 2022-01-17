#ifndef __EVENTSERVICE_H__
#define __EVENTSERVICE_H__

#include <map>
#include <zmq.hpp>
#include <vector>
#include <thread>

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
             * @brief A list of reactors that are currently up
             * 
             */
            std::vector<int> aliveReactors;

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
             * @brief Sends a fail to deliver message back to the reactor it came from.
             * 
             * @param p_sourceMsg The zmq message of where it came from
             * @param p_destMsg The zmq message of where it will go
             * @param p_message The zmq message that is the actual message
             */
            void sendFailMsg(zmq::message_t* p_sourceMsg, zmq::message_t* p_destMsg, zmq::message_t* p_message);
            /**
             * @brief Checks if the given reactor is up
             * 
             * @return true If the given reactor is alive
             * @return false If the given reactor is not alive
             */
            bool reactorIsUp(int);
    };
}

#endif // __EVENTSERVICE_H__