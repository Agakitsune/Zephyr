
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
#include "graphics/Sprite.hpp"
#include "graphics/projector/OrthographicProjector.hpp"
#include "graphics/pipeline/SpritePipeline.hpp"
#include "animation/easing/Interpolation.hpp"

// #include <experimental/simd>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

int main(void) {
    // zephyr::::Window window(800, 600, "WindowTest");
    zephyr::graphics::Window window(800, 600, "WindowTest");
    zephyr::graphics::Sprite sprite("../poyo.png");
    zephyr::graphics::OrthographicProjector projector(800, 600);
    zephyr::graphics::SpritePipeline pipeline("../shader.vs", "../shader.fs");
    zephyr::animation::Interpolation<zephyr::math::vec2f> interpolation;

    window.usePipeline(pipeline);
    window.useProjector(projector);

    sprite.scale(16, 16);

    interpolation.interpolate(zephyr::animation::easing::bounceOut, zephyr::math::vec2f(0,0), zephyr::math::vec2f(100,100), 128);

    while (window.isOpen()) {
        window.clear(zephyr::graphics::spring_green);

        window.draw(sprite);

        sprite.setPosition(interpolation.next());

        window.display();
        window.pollEvents();
    }

    return 0;
}
