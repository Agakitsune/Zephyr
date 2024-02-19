
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    class StreamSprite : public BaseSprite {
        virtual gl::BufferUsage usage() const override {
            return gl::BufferUsage::StreamDraw;
        }
        
        public:
            using BaseSprite::BaseSprite;

            virtual ~StreamSprite() override {}
    };

}
