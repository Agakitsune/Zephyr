
#pragma once

#include "gl/VertexArray.hpp"
#include "gl/Buffer.hpp"

#include "graphics/Transformable.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Colorable.hpp"
#include "graphics/font/Font.hpp"

#include "utils/VertexData.hpp"

namespace zephyr::graphics {

    class Text : public Transformable, public Drawable, public Colorable {
        Font *_font = nullptr;
        gl::Buffer _buffer;
        int _size = 0;
        
        public:
            Text() = default;
            Text(const Text &other) = default;
            Text(Text &&other) = default;
            Text(Font &font);
            Text(Font *font);

            Text &operator=(const Text &other) = default;
            Text &operator=(Text &&other) = default;

            void setFont(Font &font);
            void setFont(Font *font);

            void setText(const std::string &text);

            void draw(const Window &window, const Pipeline &pipeline) const override;
            void draw(const Window &window, const float z, const Pipeline &pipeline) const override;
            void setup(const Pipeline &pipeline) const override;
    };

}
