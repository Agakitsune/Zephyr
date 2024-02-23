
#include "graphics/pipeline/SpritePipeline.hpp"
#include "utils/VertexArray.hpp"

namespace zephyr::graphics {

    void setupVertexArray(const gl::VertexArray &array) {
        array.bind();
        zephyr::utils::useVertex<zephyr::math::vec2f, zephyr::math::vec2f>(0);
    }

    SpritePipeline::SpritePipeline(const std::string &file)
        : Pipeline(file, setupVertexArray)
    {}

    SpritePipeline::SpritePipeline(const std::filesystem::path &file)
        : Pipeline(file, setupVertexArray)
    {}

    SpritePipeline::SpritePipeline(const std::string &vertexPath, const std::string &fragmentPath)
        : Pipeline(vertexPath, fragmentPath, setupVertexArray)
    {}

    SpritePipeline::SpritePipeline(const std::string &vertexPath, const std::string &geometryPath, const std::string &fragmentPath)
        : Pipeline(vertexPath, geometryPath, fragmentPath, setupVertexArray)
    {}

    SpritePipeline::SpritePipeline(const gl::Program &program)
        : Pipeline(program)
    {}

    SpritePipeline::SpritePipeline(gl::Program &&program)
        : Pipeline(program)
    {}

}
