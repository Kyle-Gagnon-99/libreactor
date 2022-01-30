#include "spdlog/spdlog.h"
#include "FullReactor.h"
#include <string>

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    reactor::EventService evService;
    evService.start();

    FullReactor fullReactor(5);
    fullReactor.start();

    //FullReactor secondFullReactor(10);
    //secondFullReactor.start();

    std::string str = "This is rid 5 sending to rid 5!";

    fullReactor.sendMessage(5, str);
    //fullReactor.sendMessage(10, "This is rid 5 sending to rid 10!");
    //secondFullReactor.sendMessage(5, "This is rid 10 sending to rid 5!");

    return 0;
}