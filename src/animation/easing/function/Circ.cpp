
#include "animation/easing/function/Circ.hpp"

namespace zephyr::animation::easing {
    
    float circIn(float x) {
        return 1 - std::sqrt(1 - std::pow(x, 2));
    }

    float circOut(float x) {
        return std::sqrt(1 - std::pow(x - 1, 2));
    }

    float circInOut(float x) {
        return x < 0.5f
            ? (1 - std::sqrt(1 - std::pow(2 * x, 2))) / 2
            : (std::sqrt(1 - std::pow(-2 * x + 2, 2)) + 1) / 2;
    }

} // namespace zephyr::animation::easing
