#include <string>
#include "spdlog/spdlog.h"
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "FullReactor.h"

FullReactor::FullReactor(int p_rid) : reactor::Reactor(p_rid) {
    
}

FullReactor::FullReactor(int p_rid, std::string p_conEndPoint) : reactor::Reactor(p_rid, p_conEndPoint) {
    
}

void FullReactor::consumeMsg(std::string p_msg) {
    spdlog::debug("RID {} RECEIVED: {}", rid, p_msg);
}

void FullReactor::processFailMsg(std::string p_failMsgStr, int p_dest) {
    spdlog::debug("RID {} failed to deliver to {}", rid, p_dest);
}

FullReactor::~FullReactor() {
    thread_object.join();
}