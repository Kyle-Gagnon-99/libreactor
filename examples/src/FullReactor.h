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
         * @brief Connect to an endpoint with a specificed ID
         * 
         */
        FullReactor(int p_rid, std::string p_conEndPoint);
        virtual ~FullReactor();
        /**
         * @brief Consumes the message and prints the message out
         * 
         * @param p_msg The message to consume
         */
        void consumeMessage(std::string p_msg);

        /**
         * @brief Implements virtual function. Processes fail message from router. In this case do nothing
         * 
         * @param p_failMsgStr The failed message type
         * @param p_dest Where the message was supposed to go
         */
        void processFailMessage(int p_destRid, std::string p_failMsgStr, std::string p_message, int p_numOfAttempts);

};
#endif // __FULLREACTOR_H__