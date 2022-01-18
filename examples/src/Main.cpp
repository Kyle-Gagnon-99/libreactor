#include "spdlog/spdlog.h"
#include "FullReactor.h"

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    reactor::EventService evService;
    evService.start();

    FullReactor fullReactor(5, &evService);
    fullReactor.start();

    FullReactor secondFullReactor(10, &evService);
    secondFullReactor.start();


    fullReactor.sendMessage(5, "This is rid 5 sending to rid 5!");
    fullReactor.sendMessage(10, "This is rid 5 sending to rid 10!");
    secondFullReactor.sendMessage(5, "This is rid 10 sending to rid 5!");

    return 0;
}