#include <string>
#include "spdlog/spdlog.h"
#include "reactor/Reactor.h"
#include "reactor/EventService.h"
#include "FullReactor.h"

FullReactor::FullReactor(int p_rid, reactor::EventService* p_evService) : reactor::Reactor(p_rid, p_evService) {
    spdlog::debug("Called Full Reactor constructor");
}

void FullReactor::consumeMsg(std::string p_msg) {
    spdlog::debug("Here is the consume msg function");

    spdlog::debug("{}", p_msg);
}

FullReactor::~FullReactor() {
    thread_object.join();
}