
#include "math/matrix.hpp"

namespace zephyr::utils {

    math::matrix<4, 4, float> ortho(float left, float top, float right, float bottom, float near, float far) {
        math::matrix<4, 4, float> result(1.0f);
        result[0][0] = 2.0f / (right - left);
        result[1][1] = 2.0f / (top - bottom);
        result[2][2] = - 2.0f / (far - near);
        result[0][3] = -(right + left) / (right - left);
        result[1][3] = -(top + bottom) / (top - bottom);
        result[2][3] = -(far + near) / (far - near);
        return result;
    }

    math::matrix<4, 4, float> perspective(float fov, float aspect, float near, float far) {
        math::matrix<4, 4, float> result(0.0f);
        // calculate cotangent of fov / 2
        float tan = std::tan((fov * M_PI / 180) / 2.0f);
        result[0][0] = 1.0f / (tan * aspect);
        result[1][1] = 1.0f / tan;
        result[2][2] = -(far + near) / (far - near);
        result[3][2] = -1.0f;
        result[2][3] = -(2.0f * far * near) / (far - near);
        return result;
    }

} // namespace zephyr::utils
