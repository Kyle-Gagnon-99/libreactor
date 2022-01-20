#include <string>
#include "spdlog/spdlog.h"
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "FullReactor.h"

FullReactor::FullReactor(int p_rid) : reactor::Reactor(p_rid) {
    
}

void FullReactor::consumeMsg(std::string p_msg) {
    spdlog::debug("RID {} RECEIVED: {}", rid, p_msg);
}

FullReactor::~FullReactor() {
    thread_object.join();
}