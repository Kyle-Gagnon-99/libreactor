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
        FullReactor(int p_rid, reactor::EventService* p_evService);
        /**
         * @brief Destroy the Full Reactor object
         * 
         */
        ~FullReactor();
        /**
         * @brief The message to consume
         * 
         * @param p_msg 
         */
        void consumeMsg(std::string p_msg);

};
#endif // __FULLREACTOR_H__