
#include "animation/easing/function/Bounce.hpp"

namespace zephyr::animation::easing {
    
    float bounceIn(float x) {
        return 1 - bounceOut(1 - x);
    }

    float bounceOut(float x) {
        constexpr float n1 = 7.5625;
        constexpr float d1 = 2.75;

        if (x < 1 / d1) {
            return n1 * x * x;
        } else if (x < 2 / d1) {
            x = x - 1.5 / d1;
            return n1 * x * x + 0.75;
        } else if (x < 2.5 / d1) {
            x = x - 2.25 / d1;
            return n1 * x * x + 0.9375;
        } else {
            x = x - 2.625 / d1;
            return n1 * x * x + 0.984375;
        }
    }

    float bounceInOut(float x) {
        return x < 0.5f
            ? (1 - bounceOut(1 - 2 * x)) / 2
            : (1 + bounceOut(2 * x - 1)) / 2;
    }

} // namespace zephyr::animation::easing
