
#pragma once

#include <string>
#include <fstream>
#include <unordered_map>

#include "graphics/Image.hpp"
#include "graphics/Texture.hpp"
#include "utils/Texture.hpp"

#include "graphics/font/Char.hpp"

namespace zephyr::graphics {

    class Font {
        Image _img;
        Texture _texture;

        math::vec2i _size;
        int _origin;
        int _spacing;

        std::unordered_map<char, Char> _chars;

        Char generateChar(int x, int y);

        public:
            Font() = default;
            Font(const Font &other) = default;
            Font(Font &&other) = default;
            Font(const std::string &file);

            Font &operator=(const Font &other) = default;
            Font &operator=(Font &&other) = default;

            void load(const std::string &file);

            const Texture &getTexture() const;
            math::vec2i getSize() const;
            int getOrigin() const;
            int getSpacing() const;
            const Char &getChar(char c) const;
    };

}
