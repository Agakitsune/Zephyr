
#include "animation/easing/function/Quart.hpp"

namespace zephyr::animation::easing {
    
    float quartIn(float x) {
        return std::pow(x, 4);
    }

    float quartOut(float x) {
        return 1 - std::pow(1 - x, 4);
    }

    float quartInOut(float x) {
        return x < 0.5f
            ? 8 * std::pow(x, 4)
            : 1 - std::pow(-2 * x + 2, 4) / 2;
    }

} // namespace zephyr::animation::easing
