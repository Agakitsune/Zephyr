
#include "__head.h"
#include "glfw/Window.hpp"
#include "input/Keyboard.hpp"

void construct() {
    zephyr::input::underground::display = XOpenDisplay(nullptr);
    std::cout << "Construct" << std::endl;
}

void destruct() {
    XCloseDisplay(zephyr::input::underground::display);
    zephyr::glfw::Window::terminate();
    std::cout << "Destruct" << std::endl;
}
