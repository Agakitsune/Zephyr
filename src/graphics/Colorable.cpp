
#include "graphics/Colorable.hpp"

namespace zephyr::graphics {

    void Colorable::setColor(const color &c) {
        _color = c;
    }

    const color &Colorable::getColor() const {
        return _color;
    }

}
