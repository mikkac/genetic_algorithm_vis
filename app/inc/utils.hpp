#pragma once

#include <limits>

namespace gen {
double random_d(double range_min = 0.0, double range_max = 1.0);
int random_i(int range_min = std::numeric_limits<int>::min(),
                   int range_max = std::numeric_limits<int>::max());
}  // namespace gen