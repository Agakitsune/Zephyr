
#include "graphics/Texture.hpp"
#include "utils/Texture.hpp"

namespace zephyr::graphics {

    Texture::Texture() : _tex() {}

    Texture::Texture(const gl::Texture &tex) : _tex(tex) {}

    Texture::Texture(gl::Texture &&tex) : _tex(std::move(tex)) {}

    Texture::Texture(const Texture &other) : _tex(other._tex) {}

    Texture::Texture(Texture &&other) : _tex(std::move(other._tex)) {}

    Texture::Texture(const char *path) {
        _tex = utils::loadTexture(path);
    }
    
    Texture::Texture(const std::string &path) {
        _tex = utils::loadTexture(path);
    }

    Texture::Texture(const std::filesystem::path &path) {
        _tex = utils::loadTexture(path.string());
    }

    Texture::~Texture() {}

    Texture &Texture::operator=(const Texture &other) {
        _tex = other._tex;
        return *this;
    }

    Texture &Texture::operator=(Texture &&other) {
        _tex = std::move(other._tex);
        return *this;
    }

    Texture Texture::create(const int width, const int height) {
        Texture texture;
        texture._tex.bind(gl::TextureTarget::Texture2D);
        texture._tex.setTextureParameter(gl::TextureParameterName::WrapS, gl::TextureWrap::Repeat);
        texture._tex.setTextureParameter(gl::TextureParameterName::WrapT, gl::TextureWrap::Repeat);
        texture._tex.setTextureParameter(gl::TextureParameterName::MinFilter, gl::TextureFilter::NearestMipmapNearest);
        texture._tex.setTextureParameter(gl::TextureParameterName::MagFilter, gl::TextureFilter::Nearest);
        texture._tex.data2D(0, gl::TextureInternalFormat::RGB, width, height, gl::TextureFormat::RGB, gl::TextureDataType::UnsignedByte, nullptr);
        texture._tex.generateMipmap();
        return texture;
    }

    void Texture::slot(size_t unit) const {
        _tex.activate(unit);
    }

    math::vec2u Texture::size() const {
        return _tex.size();
    }

}
