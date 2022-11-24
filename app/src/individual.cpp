#include "individual.hpp"

#include "utils.hpp"

namespace gen {

Individual::Individual() : m_value(random_i(0, 5)) {}

Individual::Individual(UnderlyingType init) : m_value{init} {}

Individual::UnderlyingType Individual::getValue() const { return m_value; }
}  // namespace gen
