#pragma once

#include <vector>

struct AlgorithmResult{
    using Data = std::vector<double>;

    Data steps{};
    Data min{};
    Data max{};
    Data avg{};
};
