
#include "__head.h"
#include "glfw/Window.hpp"
#include "input/Keyboard.hpp"

void construct() {
}

void destruct() {
    zephyr::glfw::Window::terminate();
}
