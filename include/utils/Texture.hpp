
#pragma once

#include "gl/Texture.hpp"

namespace zephyr::utils {

    gl::Texture loadTexture(const std::string &path);
    gl::Texture loadTextureFromMemory(unsigned char *data, int width, int height, int channels);

}
