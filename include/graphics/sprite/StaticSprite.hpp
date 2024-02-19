
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    // StaticSprite is an instantiable BaseSprite, this class is only there to make the name more explicit
    class StaticSprite : public BaseSprite {
        public:
            using BaseSprite::BaseSprite;

            virtual ~StaticSprite() override {}
    };

}
