
#pragma once

#include "graphics/sprite/BaseSprite.hpp"

namespace zephyr::graphics {

    class StreamSprite : public BaseSprite {
        public:
            StreamSprite(const Texture &texture);
            StreamSprite(Texture &&texture);
            StreamSprite(const char *path);
            StreamSprite(const std::string &path);
            StreamSprite(const std::filesystem::path &path);
            StreamSprite(const StreamSprite &other) = default;
            StreamSprite(StreamSprite &&other) noexcept = default;

            virtual ~StreamSprite() override {}
    };

}
