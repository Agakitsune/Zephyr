
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    class DynamicSprite : public BaseSprite {
        public:
            DynamicSprite(const Texture &texture);
            DynamicSprite(Texture &&texture);
            DynamicSprite(const char *path);
            DynamicSprite(const std::string &path);
            DynamicSprite(const std::filesystem::path &path);
            DynamicSprite(const DynamicSprite &other) = default;
            DynamicSprite(DynamicSprite &&other) noexcept = default;

            virtual ~DynamicSprite() override {}
    };

}
