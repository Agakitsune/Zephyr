
#include "gl/Buffer.hpp"

namespace zephyr::gl {

    Buffer::Buffer() {
        glGenBuffers(1, &handle);
    }

    Buffer::Buffer(Buffer&& other) noexcept {
        handle = other.handle;
        other.handle = 0;
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &handle);
    }

    Buffer& Buffer::operator=(Buffer&& other) noexcept {
        handle = other.handle;
        other.handle = 0;
        return *this;
    }

    void Buffer::bind(BufferTarget target) {
        glBindBuffer(static_cast<GLenum>(target), handle);
        this->target = target;
    }

    void Buffer::data(const void* data, size_t size, BufferUsage usage) const {
        glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
    }

    void Buffer::subData(const void* data, size_t size, size_t offset) const {
        glBufferSubData(static_cast<GLenum>(target), offset, size, data);
    }

    void Buffer::data(BufferTarget target, const void* data, size_t size, BufferUsage usage) {
        glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
    }

    void Buffer::subData(BufferTarget target, const void* data, size_t size, size_t offset) {
        glBufferSubData(static_cast<GLenum>(target), offset, size, data);
    }

} // namespace zephyr::gl
