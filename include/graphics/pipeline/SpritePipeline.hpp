
#pragma once

#include "graphics/Pipeline.hpp"
#include "utils/VertexArray.hpp"

namespace zephyr::graphics {

    class SpritePipeline : public Pipeline {
        public:
            using Pipeline::Pipeline;
            virtual ~SpritePipeline() override = default;

            virtual void setup() const override;
            virtual void reset() const override;
    };

}
