#pragma once

#include <bitset>
#include <cstdint>

namespace gen {
class Individual {
   public:
    constexpr static std::size_t Size{32};
    using UnderlyingType = std::bitset<Size>;

    explicit Individual();
    explicit Individual(UnderlyingType init);

    UnderlyingType getValue() const;

   private:
    UnderlyingType m_value;
};
}  // namespace gen
