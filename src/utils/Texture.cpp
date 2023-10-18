
#include "gl/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace zephyr::utils {

    gl::Texture loadTexture(const std::string &path) {
        int width, height, channels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            throw std::runtime_error("Failed to load texture: " + path);
        }
        std::cout << "Loaded texture: " << path << std::endl;
        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
        std::cout << "Channels: " << channels << std::endl;
        gl::Texture texture;
        texture.bind(gl::TextureTarget::Texture2D);
        texture.setTextureParameter(gl::TextureParameterName::WrapS, gl::TextureWrap::Repeat);
        texture.setTextureParameter(gl::TextureParameterName::WrapT, gl::TextureWrap::Repeat);
        texture.setTextureParameter(gl::TextureParameterName::MinFilter, gl::TextureFilter::NearestMipmapNearest);
        texture.setTextureParameter(gl::TextureParameterName::MagFilter, gl::TextureFilter::Nearest);
        if (channels == 3)
            texture.data2D(0, gl::TextureInternalFormat::RGB, width, height, gl::TextureFormat::RGB, gl::TextureDataType::UnsignedByte, data);
        else if (channels == 4)
            texture.data2D(0, gl::TextureInternalFormat::RGBA, width, height, gl::TextureFormat::RGBA, gl::TextureDataType::UnsignedByte, data);
        texture.generateMipmap();
        stbi_image_free(data);
        return texture;
    }

}
