#include "utils.hpp"

#include <random>

namespace gen {

double random_d(double range_min, double range_max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(range_min, range_max);
    return dist(gen);
}

int random_i(int range_min, int range_max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(range_min, range_max);
    return dist(gen);
}

}  // namespace gen