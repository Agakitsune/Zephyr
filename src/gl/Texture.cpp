
#include "gl/Texture.hpp"

namespace zephyr::gl {

    Texture::Texture() {
        glGenTextures(1, &handle);
    }

    Texture::Texture(Texture &&other) {
        handle = other.handle;
        other.handle = 0;
    }

    Texture::~Texture() {
        if (handle != 0) {
            glDeleteTextures(1, &handle);
        }
    }

    Texture &Texture::operator=(Texture &&other) {
        handle = other.handle;
        other.handle = 0;
        return *this;
    }

    void Texture::bind(gl::TextureTarget target) {
        glBindTexture(static_cast<GLenum>(target), handle);
        this->target = target;
    }

    void Texture::data1D(GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexImage1D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::data2D(GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, GLsizei height, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexImage2D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, height, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::data3D(GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexImage3D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, height, depth, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata1D(GLint level, GLint xoffset, GLsizei width, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexSubImage1D(static_cast<GLenum>(target), level, xoffset, width, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexSubImage2D(static_cast<GLenum>(target), level, xoffset, yoffset, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, gl::TextureFormat format, gl::TextureDataType type, void *data) const {
        glTexSubImage3D(static_cast<GLenum>(target), level, xoffset, yoffset, zoffset, width, height, depth, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::data1D(gl::TextureTarget target, GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexImage1D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::data2D(gl::TextureTarget target, GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, GLsizei height, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexImage2D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, height, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::data3D(gl::TextureTarget target, GLint level, gl::TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexImage3D(static_cast<GLenum>(target), level, static_cast<GLint>(internalFormat), width, height, depth, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata1D(gl::TextureTarget target, GLint level, GLint xoffset, GLsizei width, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexSubImage1D(static_cast<GLenum>(target), level, xoffset, width, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata2D(gl::TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexSubImage2D(static_cast<GLenum>(target), level, xoffset, yoffset, width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::subdata3D(gl::TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, gl::TextureFormat format, gl::TextureDataType type, void *data) {
        glTexSubImage3D(static_cast<GLenum>(target), level, xoffset, yoffset, zoffset, width, height, depth, static_cast<GLenum>(format), static_cast<GLenum>(type), data);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, GLfloat value) const {
        setTextureParameter(target, name, value);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, GLint value) const {
        setTextureParameter(target, name, value);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, GLfloat *value) const {
        setTextureParameter(target, name, value);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, GLint *value) const {
        setTextureParameter(target, name, value);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, GLuint *value) const {
        setTextureParameter(target, name, value);
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, gl::TextureWrap value) const {
        setTextureParameter(target, name, (int)static_cast<GLenum>(value));
    }

    void Texture::setTextureParameter(gl::TextureParameterName name, gl::TextureFilter value) const {
        setTextureParameter(target, name, (int)static_cast<GLenum>(value));
    }

    void Texture::generateMipmap() const {
        generateMipmap(target);
    }

    void Texture::activate(size_t unit) const {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(static_cast<GLenum>(target), handle);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, GLfloat value) {
        glTexParameterf(static_cast<GLenum>(target), static_cast<GLenum>(name), value);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, GLint value) {
        glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(name), value);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, GLfloat *value) {
        glTexParameterfv(static_cast<GLenum>(target), static_cast<GLenum>(name), value);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, GLint *value) {
        glTexParameteriv(static_cast<GLenum>(target), static_cast<GLenum>(name), value);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, GLuint *value) {
        glTexParameterIuiv(static_cast<GLenum>(target), static_cast<GLenum>(name), value);
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, gl::TextureFilter value) {
        glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(name), static_cast<GLenum>(value));
    }

    void Texture::setTextureParameter(gl::TextureTarget target, gl::TextureParameterName name, gl::TextureWrap value) {
        glTexParameteri(static_cast<GLenum>(target), static_cast<GLenum>(name), static_cast<GLenum>(value));
    }

    void Texture::generateMipmap(gl::TextureTarget target) {
        glGenerateMipmap(static_cast<GLenum>(target));
    }

}
