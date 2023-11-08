
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

#include <experimental/simd>

int main(void) {
    // zephyr::math::vector<5, int> a(1, 2, 3, 4, 5);
    // zephyr::math::vector<5, float> b(1, 2, 3, 4, 5);
    // std::experimental::fixed_size_simd<float, 5> c(1.5);
    // std::experimental::fixed_size_simd<int, 5> d(1);
    // c += d;

    // zephyr::glfw::Window window(800, 600, "WindowTest");

    // glewExperimental = true;
    // if (glewInit() != GLEW_OK)
    //     throw std::runtime_error("Could not initialize GLEW");

    // zephyr::gl::Texture tex = zephyr::utils::loadTexture("../cloud.png");

    // zephyr::gl::Shader vert = zephyr::utils::loadShader("../shader.vs", zephyr::gl::ShaderType::Vertex);
    // zephyr::gl::Shader frag = zephyr::utils::loadShader("../shader.fs", zephyr::gl::ShaderType::Fragment);

    // zephyr::gl::Program prog;

    // prog.attach(vert);
    // prog.attach(frag);

    // prog.link();

    // tex.activate(0);

    // zephyr::gl::Uniform uni = prog.getUniform("tex");

    // float vertices[] = {
    //     -1.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
    //     1.0f, -1.0f, 0.0f,      1.0f, 0.0f, 1.0f,       1.0f, 1.0f,
    //     -1.0f,  1.0f, 0.0f,      0.0f, 1.0f, 1.0f,       0.0f, 0.0f,
    //     1.0f,  1.0f, 0.0f,      1.0f, 1.0f, 0.0f,       1.0f, 0.0f,
    // };  

    // zephyr::math::vec2f a(4, 4);
    // zephyr::math::vec2f b(4, 4);
    // // zephyr::math::vec2f c = a % b;

    // zephyr::gl::VertexArray VAO;
    // VAO.bind();

    // zephyr::gl::Buffer VBO;

    // VBO.bind(zephyr::gl::BufferTarget::ArrayBuffer);
    // VBO.data(vertices, zephyr::gl::BufferUsage::StaticDraw);

    // zephyr::utils::useVertex<zephyr::math::vec3f, zephyr::math::vec3f, zephyr::math::vec2f>(0);

    // while (!window.shouldClose()) {
    //     window.pollEvents();

    //     window.clear(zephyr::gl::ClearMask::Color);

    //     tex.activate(0);

    //     prog.use();
    //     uni.set(0);
        
    //     VAO.bind();
    //     window.drawArrays(zephyr::gl::DrawMode::TriangleStrip, 0, 4);
    //     window.swapBuffers();
    // }

    // glfwTerminate();

    return 0;
}
