#include <string>
#include "spdlog/spdlog.h"
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "FullReactor.h"

FullReactor::FullReactor(int p_reactorId) : reactor::Reactor(p_reactorId) {
    
}

FullReactor::FullReactor(int p_reactorId, std::string p_conEndPoint) : reactor::Reactor(p_reactorId, p_conEndPoint) {
    
}

void FullReactor::consumeMsg(std::string p_msg) {
    spdlog::debug("RID {} RECEIVED: {}", reactorId, p_msg);
}

void FullReactor::processFailMsg(std::string p_failMsgStr, int p_dest) {
    spdlog::debug("RID {} failed to deliver to {}", reactorId, p_dest);
}

FullReactor::~FullReactor() {
    thread_object.join();
}