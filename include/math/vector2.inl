
#include <type_traits>

#include "vectorutils.hpp"

namespace zephyr::math {
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr T vector<2, T>::dot(const vector<2, T> &other) const {
        return zephyr::math::dot(*this, other);
    }

} // namespace zephyr::math
