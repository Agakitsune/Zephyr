
#include "graphics/Window.hpp"

namespace zephyr::graphics {
    
    void initGLState() {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    Window::Window() : _handle() {
        initGLState();
    }

    Window::Window(int width, int height, const std::string &title) : _handle(width, height, title) {
        initGLState();
    }

    Window::Window(int width, int height, std::string &&title) : _handle(width, height, title) {
        initGLState();
    }

    Window::Window(int width, int height, const char *title) : _handle(width, height, title) {
        initGLState();
    }

    Window::Window(Window &&other) noexcept : _handle(std::move(other._handle)) {
        initGLState();
    }

    Window::~Window() {}
    
    Window &Window::operator=(Window &&other) noexcept {
        _handle = std::move(other._handle);
        return *this;
    }

    void Window::create(int width, int height, const std::string &title) {
        _handle.create(width, height, title);

        initGLState();
    }

    void Window::create(int width, int height, std::string &&title) {
        _handle.create(width, height, title);

        initGLState();
    }

    void Window::create(int width, int height, const char *title) {
        _handle.create(width, height, title);

        initGLState();
    }

    bool Window::isOpen() const {
        return !_handle.shouldClose();
    }

    void Window::close() const {
        _handle.close();
    }

    void Window::destroy() {
        _handle.destroy();
    }

    void Window::pollEvents() const {
        _handle.pollEvents();
    }

    void Window::usePipeline(const Pipeline &pipeline) {
        usePipeline(&pipeline);
    }

    void Window::usePipeline(const Pipeline *pipeline) {
        if (_lastPipeline)
            _lastPipeline->unuse();
        _lastPipeline = pipeline;
        pipeline->use();
    }

    void Window::draw(const Drawable &drawable, const Pipeline *pipeline) const {
        if (pipeline) {
            if (pipeline != _lastPipeline) {
                _lastPipeline->unuse();
                pipeline->use();
                _lastPipeline = pipeline;
            }
        }
        if (_projector) {
            _projector->setup(*_lastPipeline);
        }
        drawable.setup(*_lastPipeline);
        drawable.draw(*this, *_lastPipeline);
    }

    void Window::draw(const Drawable &drawable, const float z, const Pipeline *pipeline) const {
        if (pipeline) {
            if (pipeline != _lastPipeline) {
                _lastPipeline->unuse();
                pipeline->use();
                _lastPipeline = pipeline;
            }
        }
        if (_projector) {
            _projector->setup(*_lastPipeline);
        }
        drawable.setup(*_lastPipeline);
        drawable.draw(*this, z, *_lastPipeline);
    }

    void Window::drawPrimitive(const zephyr::gl::DrawMode mode, int first, int count) const {
        _handle.drawArrays(mode, first, count);
    }

    void Window::clear(const color &color) const {
        glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
        _handle.clear(zephyr::gl::ClearMask::ColorDepth);
    }

    void Window::display() const {
        _handle.swapBuffers();
    }

    bool Window::isKeyPressed(const input::Key key) const {
        return _handle.isKeyPressed(key);
    }

    bool Window::isKeyReleased(const input::Key key) const {
        return _handle.isKeyReleased(key);
    }

    bool Window::isMouseButtonPressed(const input::MouseButton button) const {
        return _handle.isMouseButtonPressed(button);
    }

    bool Window::isMouseButtonReleased(const input::MouseButton button) const {
        return _handle.isMouseButtonReleased(button);
    }

    zephyr::math::vec2d Window::getMousePos() const {
        return _handle.getMousePos();
    }

    void Window::setMousePos(double x, double y) const {
        _handle.setMousePos(x, y);
    }

    void Window::setMousePos(const zephyr::math::vec2d &pos) const {
        _handle.setMousePos(pos.x, pos.y);
    }

    zephyr::math::vec2d Window::getMouseScroll() const {
        return _handle.getMouseScroll();
    }

    bool Window::isJoystickConnected(const input::Joystick joystick) const {
        return _handle.isJoystickConnected(joystick);
    }

    bool Window::isJoystickButtonPressed(const input::Joystick joystick, const input::JoystickButton button) const {
        return _handle.isJoystickButtonPressed(joystick, button);
    }

    bool Window::isJoystickButtonReleased(const input::Joystick joystick, const input::JoystickButton button) const {
        return _handle.isJoystickButtonReleased(joystick, button);
    }

    float Window::getJoystickAxis(const input::Joystick joystick, const input::JoystickAxis axis) const {
        return _handle.getJoystickAxis(joystick, axis);
    }

    zephyr::math::vec2f Window::getJoystickAxis(const input::Joystick joystick, const input::JoystickFullAxis axis) const {
        return _handle.getJoystickAxis(joystick, axis);
    }

    void Window::showCursor() const {
        _handle.showCursor();
    }

    void Window::hideCursor() const {
        _handle.hideCursor();
    }

    void Window::lockCursor() const {
        _handle.lockCursor();
    }

    void Window::unlockCursor() const {
        _handle.unlockCursor();
    }


}
