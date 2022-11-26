#pragma once

#include <functional>

#include "individual.hpp"

namespace gen {

struct AlgorithmConfig {
    using EstimateFunction =
        std::function<double(const Individual& individual)>;

    std::size_t population_size{};
    std::size_t steps{};
    double mutation_probability{};
    std::size_t mutated_bits_n{};
    std::size_t crossing_pos{};
    EstimateFunction estimate_func;
};
}  // namespace gen
