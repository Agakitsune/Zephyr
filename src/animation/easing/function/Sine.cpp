
#include "animation/easing/function/Sine.hpp"

namespace zephyr::animation::easing {
    
    float sineIn(float x) {
        return 1.0f - std::cos(x * PI / 2);
    }

    float sineOut(float x) {
        return std::sin(x * PI / 2);
    }

    float sineInOut(float x) {
        return 0.5f * (1.0f - std::cos(x * PI));
    }

} // namespace zephyr::animation::easing
