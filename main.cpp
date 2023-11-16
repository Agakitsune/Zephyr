
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

#include <experimental/simd>

int main(void) {
    zephyr::glfw::Window window(800, 600, "WindowTest");

    zephyr::gl::Texture tex = zephyr::utils::loadTexture("../cloud.png");
    zephyr::gl::Program prog = zephyr::utils::loadProgram("../shader.vs", "../shader.fs");
    zephyr::gl::Uniform uni = prog.getUniform("tex");

    tex.activate(0);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
        1.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f,      0.0f, 1.0f, 1.0f,       0.0f, 0.0f,
        1.0f,  1.0f, 0.0f,      1.0f, 1.0f, 0.0f,       1.0f, 0.0f,
    };  

    zephyr::gl::VertexArray VAO;
    VAO.bind();

    zephyr::gl::Buffer VBO;

    VBO.bind(zephyr::gl::BufferTarget::ArrayBuffer);
    VBO.data(vertices, zephyr::gl::BufferUsage::StaticDraw);

    zephyr::utils::useVertex<zephyr::math::vec3f, zephyr::math::vec3f, zephyr::math::vec2f>(0);

    while (!window.shouldClose()) {
        window.pollEvents();

        window.clear(zephyr::gl::ClearMask::Color);

        tex.activate(0);

        prog.use();
        uni.set(0);
        
        VAO.bind();
        window.drawArrays(zephyr::gl::DrawMode::TriangleStrip, 0, 4);
        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
