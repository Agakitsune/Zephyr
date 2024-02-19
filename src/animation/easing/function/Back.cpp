
#include "animation/easing/function/Back.hpp"

namespace zephyr::animation::easing {
    
    float backIn(float x) {
        constexpr float c1 = 1.70158f;
        constexpr float c3 = c1 + 1;

        return c3 * x * x * x - c1 * x * x;
    }

    float backOut(float x) {
        constexpr float c1 = 1.70158f;
        constexpr float c3 = c1 + 1;

        return 1 + c3 * std::pow(x - 1, 3) + c1 * std::pow(x - 1, 2);
    }

    float backInOut(float x) {
        constexpr float c1 = 1.70158f;
        constexpr float c2 = c1 * 1.525f;

        return x < 0.5f
            ? (std::pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
            : (std::pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
    }

} // namespace zephyr::animation::easing
