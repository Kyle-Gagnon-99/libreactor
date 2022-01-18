#include "spdlog/spdlog.h"
#include "FullReactor.h"

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    reactor::EventService evService;
    evService.start();

    FullReactor fullReactor(5, &evService);
    fullReactor.start();
    fullReactor.sendMessage(5, "This is a message back to itself!");

    return 0;
}