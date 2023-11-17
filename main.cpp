
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

#include <experimental/simd>

int main(void) {
    zephyr::glfw::Window window(800, 600, "WindowTest");

    zephyr::gl::Texture tex = zephyr::utils::loadTexture("../poyo.png");
    zephyr::gl::Program prog = zephyr::utils::loadProgram("../shader.vs", "../shader.fs");
    zephyr::gl::Uniform uni = prog.getUniform("tex");
    zephyr::gl::Uniform mvp = prog.getUniform("mvp");

    tex.activate(0);

    float vertices[] = {
        0.0f, 0.0f, 0.0f,       1.0f, 1.0f, 1.0f,       0.0f, 0.0f,
        16.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,       1.0f, 0.0f,
        0.0f, 16.0f, 0.0f,      1.0f, 1.0f, 1.0f,       0.0f, 1.0f,
        16.0f, 16.0f, 0.0f,     1.0f, 1.0f, 1.0f,       1.0f, 1.0f,
    };  

    zephyr::gl::VertexArray VAO;
    VAO.bind();

    zephyr::gl::Buffer VBO;

    VBO.bind(zephyr::gl::BufferTarget::ArrayBuffer);
    VBO.data(vertices, zephyr::gl::BufferUsage::StaticDraw);

    zephyr::utils::useVertex<zephyr::math::vec3f, zephyr::math::vec3f, zephyr::math::vec2f>(0);

    zephyr::math::matrix<4, 4, float> model(1.0f);
    model = zephyr::math::scale(model, zephyr::math::vector<3, float>(4, 4, 1));
    zephyr::math::matrix<4, 4, float> view(1.0f);
    zephyr::math::matrix<4, 4, float> projection = zephyr::utils::ortho(0, 0, 800, 600, 0.1f, 100.0f);

    zephyr::math::matrix<4, 4, float> MVP = model * view * projection;

    while (!window.shouldClose()) {
        window.pollEvents();

        window.clear(zephyr::gl::ClearMask::Color);

        if (window.isKeyPressed(zephyr::input::Key::W))
            std::cout << "Z" << std::endl;

        tex.activate(0);

        prog.use();
        uni.set(0);
        mvp.set4x4(1, false, &MVP[0][0]);
        
        VAO.bind();
        window.drawArrays(zephyr::gl::DrawMode::TriangleStrip, 0, 4);
        window.swapBuffers();
    }

    // glfwTerminate();

    return 0;
}
