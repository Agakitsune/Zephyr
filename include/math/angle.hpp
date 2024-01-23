
#pragma once

namespace zephyr::math {

    constexpr double toRadians(double degrees) {
        return degrees * 0.01745329251994329576923690768489;
    }

    constexpr double toDegrees(double radians) {
        return radians * 57.295779513082320876798154814105;
    }

}
