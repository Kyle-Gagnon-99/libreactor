#include <string>
#include "spdlog/spdlog.h"
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "FullReactor.h"

FullReactor::FullReactor(int p_reactorId) : reactor::Reactor(p_reactorId) {
    
}

FullReactor::FullReactor(int p_reactorId, std::string p_conEndPoint) : reactor::Reactor(p_reactorId, p_conEndPoint) {
    
}

void FullReactor::consumeMessage(std::string p_msg) {
    spdlog::debug("RID {} RECEIVED: {}", reactorId, p_msg);
}

void FullReactor::processFailMessage(int p_destRid, std::string p_failMsgStr, std::string p_message, int p_numOfAttempts) {
    //spdlog::debug("RID {} failed to deliver to {} with the number of attempts at {} with a message of {}", reactorId, p_destRid, p_numOfAttempts, p_message);

    if(p_numOfAttempts <= 3) {
        FullReactor::resendMessage(p_destRid, p_numOfAttempts, p_message);
    }
}

FullReactor::~FullReactor() {
    thread_object.join();
}