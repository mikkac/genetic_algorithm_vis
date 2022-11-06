#pragma once

#include <cstdint>

namespace gen {
class Individual {
   public:
    using UnderlyingType = int;

    explicit Individual();
    explicit Individual(UnderlyingType init);

    UnderlyingType getValue() const;

   private:
    UnderlyingType m_value;
};
}  // namespace gen