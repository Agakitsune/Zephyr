
#pragma once

#include <memory>

#include "glfw/Window.hpp"
#include "graphics/Pipeline.hpp"
#include "graphics/Drawable.hpp"
#include "graphics/Projector.hpp"
#include "graphics/Color.hpp"

namespace zephyr::graphics {

    class Window {
        glfw::Window _handle;
        mutable const Pipeline *_lastPipeline = nullptr;
        Projector *_projector = nullptr;

        public:
            Window();
            Window(int width, int height, const std::string &title);
            Window(int width, int height, std::string &&title);
            Window(int width, int height, const char *title);

            Window(const Window &other) = delete;
            Window(Window &&other) noexcept;

            ~Window();
            
            Window &operator=(const Window &other) = delete;
            Window &operator=(Window &&other) noexcept;

            void create(int width, int height, const std::string &title);
            void create(int width, int height, std::string &&title);
            void create(int width, int height, const char *title);

            bool isOpen() const;
            void close() const;
            void destroy();

            void pollEvents() const;

            void usePipeline(const Pipeline &pipeline);
            void usePipeline(const Pipeline *pipeline);

            template<typename T>
            requires std::is_base_of_v<Projector, T>
            void useProjector(T &projector) {
                _projector = &projector;
            }

            void draw(const Drawable &drawable, const Pipeline *pipeline = nullptr) const;
            void draw(const Drawable &drawable, const float z, const Pipeline *pipeline = nullptr) const;
            void drawPrimitive(const zephyr::gl::DrawMode mode, int first, int count) const;

            void clear(const color &color = black) const;

            void display() const;

            bool isKeyPressed(const input::Key key) const;
            bool isKeyRepeated(const input::Key key) const;
            bool isKeyReleased(const input::Key key) const;
            bool isKeyJustPressed(const input::Key key) const;

            bool isMouseButtonPressed(const input::MouseButton button) const;
            bool isMouseButtonReleased(const input::MouseButton button) const;

            zephyr::math::vec2d getMousePos() const;
            void setMousePos(double x, double y) const;
            void setMousePos(const zephyr::math::vec2d &pos) const;
            
            zephyr::math::vec2d getMouseScroll() const;

            bool isJoystickConnected(const input::Joystick joystick) const;

            bool isJoystickButtonPressed(const input::Joystick joystick, const input::JoystickButton button) const;
            bool isJoystickButtonReleased(const input::Joystick joystick, const input::JoystickButton button) const;

            float getJoystickAxis(const input::Joystick joystick, const input::JoystickAxis axis) const;
            zephyr::math::vec2f getJoystickAxis(const input::Joystick joystick, const input::JoystickFullAxis axis) const;

            void showCursor() const;
            void hideCursor() const;
            void lockCursor() const;
            void unlockCursor() const;
    };

}
