
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    class DynamicSprite : public BaseSprite {
        virtual gl::BufferUsage usage() const override {
            return gl::BufferUsage::DynamicDraw;
        }
        
        public:
            using BaseSprite::BaseSprite;

            virtual ~DynamicSprite() override {}
    };

}
