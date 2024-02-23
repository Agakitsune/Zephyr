
#include "gl/Texture.hpp"
#include "utils/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef ZEPHYR_DEBUG
    #include "utils/Debug.hpp"
#endif

namespace zephyr::utils {

    gl::Texture _loadTextureFromMemory(unsigned char *data, int width, int height, int channels) {
        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Texture") << "Width: " << width << std::endl;
            zephyr::debug("Texture") << "Height: " << height << std::endl;
            zephyr::debug("Texture") << "Channels: " << channels << std::endl;
        #endif

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
        return texture;
    }

    gl::Texture loadTexture(const std::string &path) {
        int width, height, channels;
        unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            throw std::runtime_error("Failed to load texture: " + path);
        }

        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Texture") << "Loading: " << path << std::endl;
        #endif

        gl::Texture tex = _loadTextureFromMemory(data, width, height, channels);
        stbi_image_free(data);
        return tex;
    }

    

    gl::Texture loadTextureFromMemory(unsigned char *data, int width, int height, int channels) {
        #ifdef ZEPHYR_DEBUG
            zephyr::debug("Texture") << "Loading from memory " << std::endl;
        #endif

        return _loadTextureFromMemory(data, width, height, channels);
    }

}
