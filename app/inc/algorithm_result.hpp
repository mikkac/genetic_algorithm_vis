#pragma once

#include <vector>

namespace gen {

struct AlgorithmResult {
    using Data = std::vector<double>;

    Data steps{};
    Data min{};
    Data max{};
    Data avg{};
};
}  // namespace gen
