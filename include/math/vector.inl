
#include <type_traits>

#include "vectorutils.hpp"

namespace zephyr::math {
    
    template<size_t N, typename T>
    requires std::is_arithmetic_v<T>
    constexpr T vector<N, T>::dot(const vector<N, T> &other) const {
        return zephyr::math::dot(*this, other);
    }

} // namespace zephyr::math
