
#include "graphics/pipeline/SpritePipeline.hpp"

namespace zephyr::graphics {

    void SpritePipeline::setup() const {
        Pipeline::setup();

        zephyr::utils::useVertex<zephyr::math::vec3f, zephyr::math::vec3f, zephyr::math::vec2f>(0);
    }

    void SpritePipeline::reset() const {
        zephyr::utils::disableAll();
    }

}
