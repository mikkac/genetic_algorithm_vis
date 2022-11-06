#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace gen {
class Configuration {
   public:
    Configuration() = default;

    int parseCmd(int argc, char** argv);

    class Options {
        friend class Configuration;

        uint8_t x{};
        std::string y{};
    };

    const Options& getOptions() const;

   private:
    Options options_{};
};
}  // namespace gen