
#include "graphics/sprite/StreamSprite.hpp"

namespace zephyr::graphics {

    StreamSprite::StreamSprite(const Texture &texture) : BaseSprite(texture, gl::BufferUsage::StreamDraw) {}

    StreamSprite::StreamSprite(Texture &&texture) : BaseSprite(std::move(texture), gl::BufferUsage::StreamDraw) {}

    StreamSprite::StreamSprite(const char *path) : BaseSprite(path, gl::BufferUsage::StreamDraw) {}

    StreamSprite::StreamSprite(const std::string &path) : BaseSprite(path, gl::BufferUsage::StreamDraw) {}

    StreamSprite::StreamSprite(const std::filesystem::path &path) : BaseSprite(path, gl::BufferUsage::StreamDraw) {}

}