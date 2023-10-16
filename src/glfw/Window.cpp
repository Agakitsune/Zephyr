
#include "glfw/Window.hpp"

namespace zephyr::glfw {
    
    Window::Window(int width, int height, const std::string &title) {
        if (!init)
            glfwInit();
        if (defaultHints) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        defaultHints = true;
    }

    Window::Window(int width, int height, std::string &&title) {
        if (!init)
            glfwInit();
        if (defaultHints) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        defaultHints = true;
    }

    Window::Window(int width, int height, const char *title) {
        if (!init)
            glfwInit();
        if (defaultHints) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        defaultHints = true;
    }

    Window::Window(Window &&other) noexcept {
        handle = other.handle;
        other.handle = nullptr;
    }

    Window::~Window() {
        if (handle != nullptr) {
            glfwDestroyWindow(handle);
        }
    }

    Window &Window::operator=(Window &&other) noexcept {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }

    bool Window::shouldClose() const {
        return glfwWindowShouldClose(handle);
    }

    void Window::setTitle(const std::string &title) {
        glfwSetWindowTitle(handle, title.c_str());
    }

    void Window::setTitle(std::string &&title) {
        glfwSetWindowTitle(handle, title.c_str());
    }

    void Window::setTitle(const char *title) {
        glfwSetWindowTitle(handle, title);
    }

    math::vec2i Window::getPos() const {
        math::vec2i pos;
        glfwGetWindowPos(handle, &pos.x, &pos.y);
        return pos;
    }

    math::vec2i Window::getSize() const {
        math::vec2i size;
        glfwGetWindowSize(handle, &size.x, &size.y);
        return size;
    }

    math::vec2i Window::getFramebufferSize() const {
        math::vec2i size;
        glfwGetFramebufferSize(handle, &size.x, &size.y);
        return size;
    }

    void Window::setPos(int x, int y) {
        glfwSetWindowPos(handle, x, y);
    }

    void Window::setPos(const math::vec2i &pos) {
        glfwSetWindowPos(handle, pos.x, pos.y);
    }

    void Window::setSize(int width, int height) {
        glfwSetWindowSize(handle, width, height);
    }

    void Window::setSize(const math::vec2i &size) {
        glfwSetWindowSize(handle, size.x, size.y);
    }

    int Window::getAttribute(WindowAttribute attrib) const {
        return glfwGetWindowAttrib(handle, static_cast<int>(attrib));
    }

    void Window::setAttribute(WindowAttribute attrib, int value) {
        glfwSetWindowAttrib(handle, static_cast<int>(attrib), value);
    }

    void Window::pollEvents() const {
        glfwPollEvents();
    }

    void Window::waitEvents() const {
        glfwWaitEvents();
    }

    void Window::waitEvents(double timeout) const {
        glfwWaitEventsTimeout(timeout);
    }

    void Window::swapBuffers() const {
        glfwSwapBuffers(handle);
    }

    void Window::setHint(WindowAttribute attrib, int value) {
        if (!init)
            glfwInit();
        glfwWindowHint(static_cast<int>(attrib), value);
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, const std::string &value) {
        if (!init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value.c_str());
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, std::string &&value) {
        if (!init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value.c_str());
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, const char *value) {
        if (!init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value);
        defaultHints = false;
    }

    bool Window::init = false;
    bool Window::defaultHints = true;

} // namespace zephyr::glfw
