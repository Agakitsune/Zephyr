
#pragma once

#include "graphics/Pipeline.hpp"
#include "graphics/Projector.hpp"
#include "graphics/font/Font.hpp"

#include "registry/Registry.hpp"

namespace zephyr {

    extern registry::Registry<graphics::Pipeline> *PIPELINE;
    extern registry::Registry<graphics::Projector> *PROJECTOR;
    extern registry::Registry<graphics::Font> *FONT;

}
