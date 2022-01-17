#include "spdlog/spdlog.h"

int main() {
    
    spdlog::set_level(spdlog::level::debug);

    spdlog::debug("Here is an example / testing");

    return 0;
}