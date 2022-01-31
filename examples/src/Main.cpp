#include "spdlog/spdlog.h"
#include "reactor/EventService.h"
#include "FullReactor.h"
#include <string>

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    reactor::EventService evService;
    evService.start();

    FullReactor fullReactor(5);
    fullReactor.start();

    FullReactor secondReactor(7);
    secondReactor.start();

    std::string str = "This is rid 5 sending to rid 7!";
    std::string anotherStr = "This is another string to rid 7!";

    fullReactor.sendMessage(7, str);
    fullReactor.sendMessage(8, anotherStr);

    return 0;
}