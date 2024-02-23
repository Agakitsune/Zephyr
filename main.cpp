
#include <iostream>
#include "unistd.h"
#include <cstring>
#include <stdio.h>

#include "math/math.hpp"

#include "glfw/Window.hpp"

#include "gl/Program.hpp"
#include "gl/Buffer.hpp"
#include "gl/VertexArray.hpp"
#include "gl/Type.hpp"
#include "gl/Texture.hpp"

#include "utils/Shader.hpp"
#include "utils/VertexArray.hpp"
#include "utils/Texture.hpp"
#include "utils/Program.hpp"
#include "utils/Clip.hpp"

#include "input/Keyboard.hpp"

#include "graphics/Window.hpp"
#include "graphics/sprite/StaticSprite.hpp"
#include "graphics/sprite/DynamicSprite.hpp"
#include "graphics/projector/OrthographicProjector.hpp"
#include "graphics/pipeline/SpritePipeline.hpp"
#include "graphics/font/Font.hpp"
#include "graphics/Text.hpp"
#include "animation/easing/Interpolation.hpp"

// #include <experimental/simd>

#include "core/Core.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

int main(void) {
    zephyr::Core::init("../resources/project.json");
    zephyr::Core::run();

    return 0;
}
