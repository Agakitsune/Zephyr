
#include <type_traits>

#include "vectorutils.hpp"

namespace zephyr::math {
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr T vector<3, T>::dot(const vector<3, T> &other) const {
        return zephyr::math::dot(*this, other);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    constexpr vector<3, T> vector<3, T>::cross(const vector<3, T> &other) const {
        return zephyr::math::cross(*this, other);
    }

} // namespace zephyr::math
