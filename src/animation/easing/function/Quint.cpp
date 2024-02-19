
#include "animation/easing/function/Quint.hpp"

namespace zephyr::animation::easing {
    
    float quintIn(float x) {
        return std::pow(x, 5);
    }

    float quintOut(float x) {
        return 1 - std::pow(1 - x, 5);
    }

    float quintInOut(float x) {
        return x < 0.5f
            ? 16 * x * x * x * x * x
            : 1 - std::pow(-2 * x + 2, 5) / 2;
    }

} // namespace zephyr::animation::easing
