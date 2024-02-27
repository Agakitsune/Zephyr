
#pragma once

#include <filesystem>

#include "gl/VertexArray.hpp"
#include "gl/Buffer.hpp"

#include "graphics/Transformable.hpp"
#include "graphics/Texture.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Colorable.hpp"

#include "math/rect.hpp"

namespace zephyr::graphics {

    class BaseSprite : public Transformable, public Drawable, public Colorable {
        Texture _texture;
        gl::Buffer _buffer;
        const gl::BufferUsage _usage;

        void setupBuffer();
        void setupBuffer(const zephyr::math::rect<int> &rect);
        void setupBuffer(const zephyr::math::rect<int> &rect, const zephyr::math::vec2u &textureSize);

        public:
            BaseSprite(const Texture &texture, gl::BufferUsage usage);
            BaseSprite(Texture &&texture, gl::BufferUsage usage);
            BaseSprite(const char *path, gl::BufferUsage usage);
            BaseSprite(const std::string &path, gl::BufferUsage usage);
            BaseSprite(const std::filesystem::path &path, gl::BufferUsage usage);
            BaseSprite(const BaseSprite &other);
            BaseSprite(BaseSprite &&other) noexcept;

            virtual ~BaseSprite() = 0;

            BaseSprite &operator=(const BaseSprite &other);
            BaseSprite &operator=(BaseSprite &&other) noexcept;

            void setPosition(const float x, const float y);
            void setPosition(const math::vec2f &position);
            void move(const float x, const float y);

            void setRotation(const float angle);
            void rotate(const float angle);

            void setScale(const float x, const float y);
            void setScale(const math::vec2f &scale);
            void scale(const float x, const float y);

            void setOrigin(const float x, const float y);
            void setOrigin(const math::vec2f &origin);

            void setTexture(const Texture &texture);
            void setTexture(Texture &&texture);
            void setTexture(const char *path);
            void setTexture(const std::string &path);
            void setTexture(const std::filesystem::path &path);

            void scissor(const int x, const int y, const int width, const int height);
            void scissor(const zephyr::math::vec2i &position, const zephyr::math::vec2i &size);
            void scissor(const zephyr::math::rect<int> &rect);

            math::vec2f getPosition() const;
            math::vec2f getScale() const;
            math::vec2f getOrigin() const;
            float getRotation() const;
            const Texture &getTexture() const;

            void draw(const Window &window, const Pipeline &pipeline) const override;
            void draw(const Window &window, const float z, const Pipeline &pipeline) const override;
            void setup(const Pipeline &pipeline) const override;
    };

}
