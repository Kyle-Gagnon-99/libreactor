#ifndef __EVENT_MESSAGE_TYPES_H__
#define __EVENT_MESSAGE_TYPES_H__

#include <string>

/**
 * @brief A list of constant variables for messages.
 */
namespace reactor {
    namespace type {

        /**
         * @brief Sends a message back to the reactor when it failed to deliver the message.
         */
        const std::string FAIL_TO_DELIVER = "FAIL_TO_DELIVER";
    }
}
#endif // __EVENT_MESSAGE_TYPES_H__