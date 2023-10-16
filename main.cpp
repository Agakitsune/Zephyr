
#include <iostream>
#include "unistd.h"
#include <cstring>
#include <stdio.h>

#include "math/vector.hpp"

#include "glfw/Window.hpp"

int main(void) {

    zephyr::glfw::Window window(800, 600, "WindowTest");

    while (!window.shouldClose()) {
        window.pollEvents();
        window.swapBuffers();
    }

    glfwTerminate();

    return 0;
}
