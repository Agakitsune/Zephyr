
#include "animation/easing/function/Elastic.hpp"

namespace zephyr::animation::easing {
    
    float elasticIn(float x) {
        constexpr float c4 = (2 * PI) / 3;

        return x == 0
            ? 0
            : x == 1
                ? 1
                : -std::pow(2, 10 * x - 10) * std::sin((x * 10 - 10.75) * c4);
    }

    float elasticOut(float x) {
        constexpr float c4 = (2 * PI) / 3;

        return x == 0
            ? 0
            : x == 1
                ? 1
                : std::pow(2, -10 * x) * std::sin((x * 10 - 0.75) * c4) + 1;
    }

    float elasticInOut(float x) {
        constexpr float c5 = (2 * PI) / 4.5;

        return x == 0
            ? 0
            : x == 1
                ? 1
                : x < 0.5f
                    ? -(std::pow(2, 20 * x - 10) * std::sin((20 * x - 11.125) * c5)) / 2
                    : (std::pow(2, -20 * x + 10) * std::sin((20 * x - 11.125) * c5)) / 2 + 1;
    }

} // namespace zephyr::animation::easing
