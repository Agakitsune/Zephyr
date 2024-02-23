
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    class StaticSprite : public BaseSprite {
        public:
            StaticSprite(const Texture &texture);
            StaticSprite(Texture &&texture);
            StaticSprite(const char *path);
            StaticSprite(const std::string &path);
            StaticSprite(const std::filesystem::path &path);
            StaticSprite(const StaticSprite &other) = default;
            StaticSprite(StaticSprite &&other) noexcept = default;

            virtual ~StaticSprite() override {}
    };

}
