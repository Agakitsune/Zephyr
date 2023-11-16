
#include "glfw/Window.hpp"

namespace zephyr::glfw {
    
    void Window::init() {
        if (!_init)
            glfwInit();
        _init = true;
    }

    void Window::glewInit() {
        if (!_glewInit) {
            glewExperimental = true;
            if (::glewInit() != GLEW_OK)
                throw std::runtime_error("Could not initialize GLEW");
        }
        _glewInit = true;
    }

    void Window::resizeCallback(GLFWwindow *window, int width, int height) {
        (void)window;
        GLint values[4];
        glGetIntegerv(GL_VIEWPORT, values);
        int x = values[0];
        int y = values[1];

        float ratio = (float)values[2] / (float)values[3];
        float Rratio = (float)values[3] / (float)values[2];

        zephyr::math::vec2i sizeW = zephyr::math::vec2f(width, width * Rratio);
        zephyr::math::vec2i sizeH = zephyr::math::vec2f(height * ratio, height);
        zephyr::math::vec2i size;

        if ((sizeW.x <= width) && (sizeW.y <= height))
            size = sizeW;
        else
            size = sizeH;

        if (height == size.y) {
            x = (width - size.x) >> 1;
            glViewport(x, y, size.x, size.y);
        } else {
            y = (height - size.y) >> 1;
            glViewport(x, y, size.x, size.y);
        }
    }

    Window::Window(int width, int height, const std::string &title) : Window(width, height, title.c_str()) {}

    Window::Window(int width, int height, std::string &&title) : Window(width, height, title) {}

    Window::Window(int width, int height, const char *title) {
        init();
        if (defaultHints) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        defaultHints = true;

        glfwMakeContextCurrent(handle);

        glfwSetFramebufferSizeCallback(handle, &resizeCallback);

        glewInit();
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

    void Window::drawArrays(gl::DrawMode mode, GLint first, GLsizei count) const {
        glDrawArrays(static_cast<GLenum>(mode), first, count);
    }

    void Window::clear(gl::ClearMask mask) const {
        glClear(static_cast<GLbitfield>(mask));
    }

    void Window::setHint(WindowAttribute attrib, int value) {
        if (!_init)
            glfwInit();
        glfwWindowHint(static_cast<int>(attrib), value);
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, const std::string &value) {
        if (!_init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value.c_str());
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, std::string &&value) {
        if (!_init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value.c_str());
        defaultHints = false;
    }

    void Window::setHint(WindowAttribute attrib, const char *value) {
        if (!_init)
            glfwInit();
        glfwWindowHintString(static_cast<int>(attrib), value);
        defaultHints = false;
    }

    bool Window::_init = false;
    bool Window::_glewInit = false;
    bool Window::defaultHints = true;

} // namespace zephyr::glfw
