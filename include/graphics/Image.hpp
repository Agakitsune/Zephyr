
#pragma once

#include <filesystem>

#include "graphics/Texture.hpp"
#include "graphics/Color.hpp"
#include "utils/Texture.hpp"
#include "math/math.hpp"

namespace zephyr::graphics {

    class Image {
        int _width, _height, _channels = 0;
        unsigned char *_data = nullptr;
        int *_refCount = nullptr;

        public:
            Image() = default;
            Image(const Image &other);
            Image(Image &&other);
            Image(const char *path);
            Image(const std::string &path);
            Image(const std::filesystem::path &path);

            ~Image();

            Image &operator=(const Image &other);
            Image &operator=(Image &&other);

            color getPixel(int x, int y) const;

            Texture toTexture() const;

            math::vec2i size() const;
    };

}
