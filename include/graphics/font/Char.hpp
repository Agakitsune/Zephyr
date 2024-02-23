
#pragma once

#include "math/rect.hpp"

namespace zephyr::graphics {

    struct Char {
        math::vector<2, int> size;
        math::rect<float> uv;
    };

}
