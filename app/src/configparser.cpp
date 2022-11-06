#include "configparser.hpp"

#include "CLI/App.hpp"
#include "CLI/Config.hpp"
#include "CLI/Formatter.hpp"
#include "spdlog/spdlog.h"

namespace gen {

int Configuration::parseCmd(int argc, char** argv) {
    CLI::App app("Example application");

    app.add_option<uint8_t>("-x, --x-param", options_.x, "Param X");
    app.add_option<std::string>("-y, --y-param", options_.y, "Param Y");

    CLI11_PARSE(app, argc, argv)  // This returns !=0 on error
    return 0;
}

const Configuration::Options& Configuration::getOptions() const {
    return options_;
}
}  // namespace gen