
#include "graphics/Image.hpp"
#include "stb_image.h"

namespace zephyr::graphics {

    Image::Image(const Image &other) {
        _data = other._data;
        _refCount = other._refCount;
        _width = other._width;
        _height = other._height;
        _channels = other._channels;
    }

    Image::Image(Image &&other) {
        _data = other._data;
        _refCount = other._refCount;
        _width = other._width;
        _height = other._height;
        _channels = other._channels;
        other._data = nullptr;
        other._refCount = nullptr;
    }

    Image::Image(const char *path) {
        _data = stbi_load(path, &_width, &_height, &_channels, 0);
        if (_data == nullptr) {
            throw std::runtime_error("Failed to load texture: " + std::string(path));
        }
        _refCount = new int(1);
    }

    Image::Image(const std::string &path) {
        _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
        if (_data == nullptr) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        _refCount = new int(1);
    }

    Image::Image(const std::filesystem::path &path) {
        _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
        if (_data == nullptr) {
            throw std::runtime_error("Failed to load texture: " + path.string());
        }
        _refCount = new int(1);
    }

    Image::~Image() {
        if (_refCount) {
            --(*_refCount);
            if (*_refCount == 0) {
                stbi_image_free(_data);
                delete _refCount;
            }
        }
    }

    Image &Image::operator=(const Image &other) {
        if (_refCount) {
            --(*_refCount);
            if (*_refCount == 0) {
                stbi_image_free(_data);
                delete _refCount;
            }
        }
        _data = other._data;
        _refCount = other._refCount;
        _width = other._width;
        _height = other._height;
        _channels = other._channels;
        return *this;
    }

    Image &Image::operator=(Image &&other) {
        if (_refCount) {
            --(*_refCount);
            if (*_refCount == 0) {
                stbi_image_free(_data);
                delete _refCount;
            }
        }
        _data = other._data;
        _refCount = other._refCount;
        _width = other._width;
        _height = other._height;
        _channels = other._channels;
        other._data = nullptr;
        other._refCount = nullptr;
        return *this;
    }

    color Image::getPixel(int x, int y) const {
        unsigned char *pixel = _data + (y * _width + x) * _channels;
        switch (_channels) {
            case 3:
                return color(pixel[0], pixel[1], pixel[2], 255);
            case 4:
                return color(pixel[0], pixel[1], pixel[2], pixel[3]);
            default:
                return color(0, 0, 0, 255);
        }
    }

    Texture Image::toTexture() const {
        return Texture(utils::loadTextureFromMemory(_data, _width, _height, _channels));
    }

    math::vec2i Image::size() const {
        return math::vec2i(_width, _height);
    }

}
