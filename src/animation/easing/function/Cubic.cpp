
#include "animation/easing/function/Cubic.hpp"

namespace zephyr::animation::easing {
    
    float cubicIn(float x) {
        return std::pow(x, 3);
    }

    float cubicOut(float x) {
        return 1 - std::pow(1 - x, 3);
    }

    float cubicInOut(float x) {
        return x < 0.5f
            ? 4 * x * x * x
            : 1 - std::pow(-2 * x + 2, 3) / 2;
    }

} // namespace zephyr::animation::easing
