
#include "graphics/sprite/StaticSprite.hpp"

namespace zephyr::graphics {

    StaticSprite::StaticSprite(const Texture &texture) : BaseSprite(texture, gl::BufferUsage::StaticDraw) {}

    StaticSprite::StaticSprite(Texture &&texture) : BaseSprite(std::move(texture), gl::BufferUsage::StaticDraw) {}

    StaticSprite::StaticSprite(const char *path) : BaseSprite(path, gl::BufferUsage::StaticDraw) {}

    StaticSprite::StaticSprite(const std::string &path) : BaseSprite(path, gl::BufferUsage::StaticDraw) {}

    StaticSprite::StaticSprite(const std::filesystem::path &path) : BaseSprite(path, gl::BufferUsage::StaticDraw) {}

}