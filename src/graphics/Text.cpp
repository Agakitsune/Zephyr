
#include <vector>

#include "graphics/Text.hpp"
#include "graphics/Pipeline.hpp"
#include "graphics/Window.hpp"

namespace zephyr::graphics {

    Text::Text(Font &font) : _font(&font) {}

    Text::Text(Font *font) : _font(font) {}

    void Text::setFont(Font &font) {
        _font = &font;
    }

    void Text::setFont(Font *font) {
        _font = font;
    }

    void Text::setText(const std::string &text) {
        _buffer.bind(gl::BufferTarget::ArrayBuffer);

        utils::VertexData<float> data;

        math::vec2i size = _font->getSize();
        int cursor = 0;
        for (char c : text) {
            if (std::isspace(c)) {
                if (c == ' ')
                    cursor += size.x;
                continue;
            }
            Char chr = _font->getChar(c);

            // vertice 1

            data.push2(cursor, 0.f);
            data.push(chr.uv.getTopLeft());

            // vertice 2

            data.push2(cursor, size.y);
            data.push2(chr.uv.getLeft(), chr.uv.getHeight());

            // vertice 3

            data.push2(cursor + chr.size.x, size.y);
            data.push(chr.uv.getSize());

            // vertice 4

            data.push2(cursor, 0.f);
            data.push(chr.uv.getTopLeft());

            // vertice 5

            data.push2(cursor + chr.size.x, size.y);
            data.push(chr.uv.getSize());

            // vertice 6

            data.push2(cursor + chr.size.x, 0.f);
            data.push2(chr.uv.getWidth(), chr.uv.getTop());

            cursor += chr.size.x + _font->getSpacing();
        }

        _size = data.size() >> 2;

        _buffer.data(data.data(), data.bufferSize(), gl::BufferUsage::StaticDraw);
    }

    void Text::draw(const Window &window, const Pipeline &pipeline) const {
        pipeline.set("Z", 0.f);
        window.drawPrimitive(gl::DrawMode::Triangles, 0, _size);
    }

    void Text::draw(const Window &window, const float z, const Pipeline &pipeline) const {
        pipeline.set("Z", z);
        window.drawPrimitive(gl::DrawMode::Triangles, 0, _size);
    }

    void Text::setup(const Pipeline &pipeline) const {
        auto model = getModel();
        _font->getTexture().slot(0);
        
        pipeline.set4x4("model", 1, true, &model[0][0]);
        pipeline.set("Texture", 0);
        pipeline.set("color", math::vec4f(getColor()) / 255.0f);

        _buffer.bindVertex(0, 0, 16);
    }

}
