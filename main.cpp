
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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

int main(void) {
    zephyr::glfw::Window window(800, 600, "WindowTest");

    zephyr::gl::Texture tex = zephyr::utils::loadTexture("../poyo.png");
    zephyr::gl::Program prog = zephyr::utils::loadProgram("../shader.vs", "../shader.fs");
    zephyr::gl::Uniform uni = prog.getUniform("tex");
    // zephyr::gl::Uniform a = prog.getUniform("model");
    // zephyr::gl::Uniform b = prog.getUniform("projection");
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
    // model = zephyr::math::scale(model, zephyr::math::vector<3, float>(4, 4, 1));
    zephyr::math::matrix<4, 4, float> view(1.0f);
    view = zephyr::math::translate(view, zephyr::math::vector<3, float>(0, 0, -50));
    zephyr::math::matrix<4, 4, float> projection = zephyr::utils::perspective(45.0f, 800.0f / 600.0f, 0.0f, 100.0f);
    // zephyr::math::matrix<4, 4, float> projection = zephyr::utils::ortho(0, 0, 800, 600, 0.0f, 100.0f);

    zephyr::math::matrix<4, 4, float> MVP = projection * view * model;
    // std::cout << MVP << std::endl;

    // window.lockCursor();

    while (!window.shouldClose()) {
        window.clear(zephyr::gl::ClearMask::Color);

        if (window.isKeyPressed(zephyr::input::Key::W))
            std::cout << "Z" << std::endl;

        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Cross) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Triangle) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Square) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Circle) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::LeftBumper) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::RightBumper) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::DpadUp) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::DpadDown) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::DpadLeft) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::DpadRight) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Guide) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Back) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::Start) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::LeftThumb) << std::endl;
        std::cout << window.isJoystickButtonPressed(zephyr::input::Joystick1, zephyr::input::JoystickButton::RightThumb) << std::endl;
        std::cout << window.getJoystickAxis(zephyr::input::Joystick1, zephyr::input::JoystickFullAxis::Left) << std::endl;
        std::cout << window.getJoystickAxis(zephyr::input::Joystick1, zephyr::input::JoystickFullAxis::Right) << std::endl;
        std::cout << window.getJoystickAxis(zephyr::input::Joystick1, zephyr::input::JoystickFullAxis::Trigger) << std::endl;

        tex.activate(0);

        prog.use();
        uni.set(0);
        // a.set4x4(1, false, &model[0][0]);
        // b.set4x4(1, false, &projection[0][0]);
        mvp.set4x4(1, true, &MVP[0][0]);
        // mvp.set4x4(1, false, &glmMVP[0][0]);
        
        VAO.bind();
        window.drawArrays(zephyr::gl::DrawMode::TriangleStrip, 0, 4);
        window.swapBuffers();
        window.pollEvents();
    }

    // glfwTerminate();

    return 0;
}
