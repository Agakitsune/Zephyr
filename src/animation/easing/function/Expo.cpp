
#include "animation/easing/function/Expo.hpp"

namespace zephyr::animation::easing {
    
    float expoIn(float x) {
        return x == 0 ? 0 : std::pow(2, 10 * x - 10);
    }

    float expoOut(float x) {
        return x == 1 ? 1 : 1 - std::pow(2, -10 * x);
    }

    float expoInOut(float x) {
        return x == 0
            ? 0
            : x == 1
                ? 1
                : x < 0.5f
                    ? std::pow(2, 20 * x - 10) / 2
                    : (2 - std::pow(2, -20 * x + 10)) / 2;
    }

} // namespace zephyr::animation::easing
