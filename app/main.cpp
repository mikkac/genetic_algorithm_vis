#include <spdlog/spdlog.h>

#include "configparser.hpp"
#include "environment.hpp"
#include "utils.hpp"

int main(int argc, char** argv) {
    // gen::Configuration config;
    // int parsing_result{};
    // if (argc > 1) {
    //     spdlog::info("Parameters will be loaded from CMD");
    //     if (const auto parsing_result{config.parseCmd(argc, argv)};
    //         parsing_result)
    //         return parsing_result;
    // }

    gen::Environment env{10, [](const gen::Individual& individual) -> double {
                             const auto x{individual.getValue()};
                             return x * x;
                         }};

    env.run(1);

    return 0;
}