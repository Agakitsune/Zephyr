
#include "animation/easing/function/Quad.hpp"

namespace zephyr::animation::easing {
    
    float quadIn(float x) {
        return x * x;
    }

    float quadOut(float x) {
        return 1 - (1 - x) * (1 - x);
    }

    float quadInOut(float x) {
        return x < 0.5f
            ? 2 * x * x
            : 1 - std::pow(-2 * x + 2, 2) / 2;
    }

} // namespace zephyr::animation::easing
