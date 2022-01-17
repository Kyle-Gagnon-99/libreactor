#ifndef __EVENT_MESSAGE_TYPES_H__
#define __EVENT_MESSAGE_TYPES_H__

#include <string>

/**
 * @brief Sets up variables for messages
 * 
 */
namespace reactor {
    namespace type {
        /**
         * @brief Message type for startup
         * 
         */
        const std::string STARTUP = "STARTUP";

        /**
         * @brief Message type for when to ignore the message
         * 
         */
        const std::string IGNORE_MSG = "IGNORE_MSG";

        /**
         * @brief Sends a message back to the reactor when it failed to deliver the message
         * 
         */
        const std::string FAIL_TO_DELIVER = "FAIL_TO_DELIVER";

        // Try to deliver or guarentee delivery
        const std::string BEST_EFFORT = "BEST_EFFORT";
        const std::string GUARENTEE = "GUARENTEE";
    }
}
#endif // __EVENT_MESSAGE_TYPES_H__