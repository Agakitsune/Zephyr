
#include "json.hpp"
#include "stb_image.h"
#include "graphics/font/Font.hpp"

#ifdef ZEPHYR_DEBUG
    #include "utils/Debug.hpp"
#endif

namespace zephyr::graphics {

    Char Font::generateChar(int x, int y) {
        int stopY = 0;

        int xMax = 0;
        int yMax = 0;

        for (int i = _size.x - 1; i >= 0; i--) {
            for (int j = _size.y - 1; j >= stopY; j--) {
                if (_img.getPixel(x + i, y + j).a > 0) {
                    if (i > xMax) {
                        xMax = i;
                    }
                    if (j > yMax) {
                        yMax = j;
                        stopY = j;
                    }
                    break;
                }
            }
        }

        return Char(
            math::vec2i(xMax + 1, _size.y),
            math::rect<float>(
                static_cast<float>(x) / _img.size().x,
                static_cast<float>(y) / _img.size().y,
                static_cast<float>(x + xMax + 1) / _img.size().x,
                static_cast<float>(y + _size.y) / _img.size().y
            )
        );
    }

    Font::Font(const std::string &file) {
        load(file);
    }

    void Font::load(const std::string &file) {
        std::ifstream fileStream(file);
        if (!fileStream.is_open())
            throw std::runtime_error("Could not open file: " + file);

        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Font") << "Loading from: " << file << std::endl;
        #endif

        nlohmann::json j;
        fileStream >> j;
        fileStream.close();

        std::filesystem::path path = file;

        _img = Image(path.parent_path() / "../textures" / j["texture"].get<std::string>());
        _texture = _img.toTexture();
        math::vec2i size = _img.size();

        _size = math::vec2i(j["size"]["width"].get<int>(), j["size"]["height"].get<int>());
        _origin = j["origin"].get<int>();
        _spacing = j["spacing"].get<int>();

        int x = size.x / _size.x;

        for (int c = 32; c < 127; c++) {
            _chars[c] = generateChar(c % x * _size.x, c / x * _size.y);
        }
    }

    const Texture &Font::getTexture() const {
        return _texture;
    }

    math::vec2i Font::getSize() const {
        return _size;
    }

    int Font::getOrigin() const {
        return _origin;
    }

    int Font::getSpacing() const {
        return _spacing;
    }

    const Char &Font::getChar(char c) const {
        return _chars.at(c);
    }

}
