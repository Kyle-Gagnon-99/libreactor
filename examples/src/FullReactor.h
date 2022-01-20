#ifndef __FULLREACTOR_H__
#define __FULLREACTOR_H__

#include "reactor/Reactor.h"

/**
 * @brief This is the fully implemented reactor from the library
 * 
 */
class FullReactor : public reactor::Reactor {

    public:
        /**
         * @brief Construct a new Full Reactor object
         * 
         * @param p_rid Ids the reactor
         * @param p_evService Fully constructed event service
         * 
         */
        FullReactor(int p_rid);
        /**
         * @brief Destroy the Full Reactor object
         * 
         */
        virtual ~FullReactor();
        /**
         * @brief Consumes the message and prints the message out
         * 
         * @param p_msg The message to consume
         */
        void consumeMsg(std::string p_msg);

        /**
         * @brief Implements virtual function. Processes fail message from router. In this case do nothing
         * 
         * @param p_failMsgStr The failed message type
         * @param p_dest Where the message was supposed to go
         */
        void processFailMsg(std::string p_failMsgStr, int p_dest);

};
#endif // __FULLREACTOR_H__