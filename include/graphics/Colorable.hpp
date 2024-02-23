
#pragma once

#include "Color.hpp"

namespace zephyr::graphics {

    class Colorable {
        color _color = white;

        public:
            Colorable() = default;
            virtual ~Colorable() = default;

            void setColor(const color &c);

            const color &getColor() const;
    };

}
