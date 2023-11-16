
#pragma once

#include "math/matrix.hpp"

namespace zephyr::utils {

    /**
     * @brief Returns an orthographic projection matrix.
     * 
     * @param left The coordinate for the left vertical clipping plane.
     * @param right The coordinate for the right vertical clipping plane.
     * @param bottom The coordinate for the bottom horizontal clipping plane.
     * @param top The coordinate for the top horizontal clipping plane.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @return math::matrix<4, 4, float> The orthographic projection matrix.
     */
    math::matrix<4, 4, float> ortho(float left, float top, float right, float bottom, float near, float far);

    /**
     * @brief Returns a perspective projection matrix.
     * 
     * @param fov The field of view angle in degrees.
     * @param aspect The aspect ratio of the projection.
     * @param near The distance to the near clipping plane.
     * @param far The distance to the far clipping plane.
     * @return math::matrix<4, 4, float> The perspective projection matrix.
     */
    math::matrix<4, 4, float> perspective(float fov, float aspect, float near, float far);

} // namespace zephyr::util
