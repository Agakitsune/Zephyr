
#include "graphics/sprite/DynamicSprite.hpp"

namespace zephyr::graphics {

    DynamicSprite::DynamicSprite(const Texture &texture) : BaseSprite(texture, gl::BufferUsage::DynamicDraw) {}

    DynamicSprite::DynamicSprite(Texture &&texture) : BaseSprite(std::move(texture), gl::BufferUsage::DynamicDraw) {}

    DynamicSprite::DynamicSprite(const char *path) : BaseSprite(path, gl::BufferUsage::DynamicDraw) {}

    DynamicSprite::DynamicSprite(const std::string &path) : BaseSprite(path, gl::BufferUsage::DynamicDraw) {}

    DynamicSprite::DynamicSprite(const std::filesystem::path &path) : BaseSprite(path, gl::BufferUsage::DynamicDraw) {}

}