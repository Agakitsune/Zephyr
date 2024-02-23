
#pragma once

#include "gl/VertexArray.hpp"

#include "graphics/Pipeline.hpp"

namespace zephyr::graphics {

    class SpritePipeline : public Pipeline {

        public:
            SpritePipeline(const std::string &file);
            SpritePipeline(const std::filesystem::path &file);
            SpritePipeline(const std::string &vertexPath, const std::string &fragmentPath);
            SpritePipeline(const std::string &vertexPath, const std::string &geometryPath, const std::string &fragmentPath);
            SpritePipeline(const gl::Program &program);
            SpritePipeline(gl::Program &&program);
            SpritePipeline(const SpritePipeline &other) = default;
            SpritePipeline(SpritePipeline &&other) noexcept = default;
            virtual ~SpritePipeline() override = default;
    };

}
