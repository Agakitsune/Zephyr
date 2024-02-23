
#include "registry/Registries.hpp"

namespace zephyr {

    registry::Registry<graphics::Pipeline> *PIPELINE = nullptr;
    registry::Registry<graphics::Projector> *PROJECTOR = nullptr;
    registry::Registry<graphics::Font> *FONT = nullptr;

}
