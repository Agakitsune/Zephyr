
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

    void Window::scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
        (void)window;
        if (current) {
            current->xoffset = xoffset;
            current->yoffset = yoffset;
        }
    }

    void Window::terminate() {
        glfwTerminate();
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
        glfwSetScrollCallback(handle, &scrollCallback);

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

    void Window::close() const {
        glfwSetWindowShouldClose(handle, true);
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
        current = const_cast<Window *>(this);
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

    bool Window::isKeyPressed(const input::Key key) const {
        return glfwGetKey(handle, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool Window::isKeyReleased(const input::Key key) const {
        return glfwGetKey(handle, static_cast<int>(key)) == GLFW_RELEASE;
    }

    bool Window::isMouseButtonPressed(const input::MouseButton button) const {
        return glfwGetMouseButton(handle, static_cast<int>(button)) == GLFW_PRESS;
    }

    bool Window::isMouseButtonReleased(const input::MouseButton button) const {
        return glfwGetMouseButton(handle, static_cast<int>(button)) == GLFW_RELEASE;
    }

    zephyr::math::vec2d Window::getMousePos() const {
        zephyr::math::vec2d pos;
        glfwGetCursorPos(handle, &pos.x, &pos.y);
        return pos;
    }

    void Window::setMousePos(double x, double y) const {
        glfwSetCursorPos(handle, x, y);
    }

    void Window::setMousePos(const zephyr::math::vec2d &pos) const {
        glfwSetCursorPos(handle, pos.x, pos.y);
    }

    zephyr::math::vec2d Window::getMouseScroll() const {
        zephyr::math::vec2d scroll = zephyr::math::vec2d(xoffset, yoffset);
        current = const_cast<Window *>(this);
        scrollCallback(handle, 0, 0);
        return scroll;
    }

    bool Window::isJoystickConnected(const input::Joystick joystick) const {
        return glfwJoystickIsGamepad(static_cast<int>(joystick));
    }

    bool Window::isJoystickButtonPressed(const input::Joystick joystick, const input::JoystickButton button) const {
        GLFWgamepadstate state;

        if (glfwGetGamepadState(static_cast<int>(joystick), &state)) {
            return state.buttons[static_cast<int>(button)] == GLFW_PRESS;
        }
        return false;
    }

    bool Window::isJoystickButtonReleased(const input::Joystick joystick, const input::JoystickButton button) const {
        return !isJoystickButtonPressed(joystick, button);
    }

    float Window::getJoystickAxis(const input::Joystick joystick, const input::JoystickAxis axis) const {
        GLFWgamepadstate state;

        if (glfwGetGamepadState(static_cast<int>(joystick), &state)) {
            switch (axis) {
                case input::JoystickAxis::LeftX:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Left).x;
                case input::JoystickAxis::LeftY:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Left).y;
                case input::JoystickAxis::RightX:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Right).x;
                case input::JoystickAxis::RightY:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Right).y;
                case input::JoystickAxis::LeftTrigger:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Trigger).x;
                case input::JoystickAxis::RightTrigger:
                    return getJoystickAxis(joystick, input::JoystickFullAxis::Trigger).y;
            }
        }
        return 0.0f;
    }

    zephyr::math::vec2f Window::getJoystickAxis(const input::Joystick joystick, const input::JoystickFullAxis axis) const {
        GLFWgamepadstate state;

        float x = 0.0f;
        float y = 0.0f;
        float value = 0.0f;
        float reduced = 0.0f;
        float angle = 0.0f;
        if (glfwGetGamepadState(static_cast<int>(joystick), &state)) {
            switch (axis) {
                case input::JoystickFullAxis::Left:
                    x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
                    y = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
                    value = std::pow(x, 2) + std::pow(y, 2);
                    reduced = std::clamp<float>((1 / (1 - deadZones[joystick].leftZone)) * (value - deadZones[joystick].leftZone), 0.0f, 1.0f);
                    angle = std::atan2(y, x);
                    x = reduced * std::cos(angle);
                    y = reduced * std::sin(angle);
                    break;
                case input::JoystickFullAxis::Right:
                    x = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_X];
                    y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y];
                    value = std::pow(x, 2) + std::pow(y, 2);
                    reduced = std::clamp<float>((1 / (1 - deadZones[joystick].leftZone)) * (value - deadZones[joystick].leftZone), 0.0f, 1.0f);
                    angle = std::atan2(y, x);
                    x = reduced * std::cos(angle);
                    y = reduced * std::sin(angle);
                    break;
                case input::JoystickFullAxis::Trigger:
                    x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER];
                    y = state.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER];
                    break;
            }
        }
        return zephyr::math::vec2f(x, y);
    }

    void Window::showCursor() const {
        glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void Window::hideCursor() const {
        glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void Window::lockCursor() const {
        glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    void Window::unlockCursor() const {
        glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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

    Window *Window::current = nullptr;

    bool Window::_init = false;
    bool Window::_glewInit = false;
    bool Window::defaultHints = true;

} // namespace zephyr::glfw
