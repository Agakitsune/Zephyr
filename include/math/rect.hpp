
#pragma once

#include "vector2.hpp"

namespace zephyr::math {

    template<typename T>
    requires std::is_arithmetic_v<T>
    class rect {
        vector<2, T> position;
        vector<2, T> size;

        public:
            rect() = default;
            rect(const vector<2, T> &position, const vector<2, T> &size) :
                position(position),
                size(size)
            {}
            rect(const T x, const T y, const T width, const T height) :
                position(x, y),
                size(width, height)
            {}

            rect(const rect &other) = default;
            rect(rect &&other) = default;

            rect &operator=(const rect &other) = default;
            rect &operator=(rect &&other) = default;

            void setPosition(const vector<2, T> &position) {
                this->position = position;
            }

            void setPosition(const T x, const T y) {
                position.x = x;
                position.y = y;
            }

            void move(const vector<2, T> &offset) {
                position += offset;
            }

            void move(const T x, const T y) {
                position.x += x;
                position.y += y;
            }

            void setSize(const vector<2, T> &size) {
                this->size = size;
            }

            void setSize(const T width, const T height) {
                size.x = width;
                size.y = height;
            }

            void scale(const vector<2, T> &scale) {
                size *= scale;
            }

            void scale(const T x, const T y) {
                size.x *= x;
                size.y *= y;
            }

            void scale(const T f) {
                size *= f;
            }

            vector<2, T> getPosition() const {
                return position;
            }

            vector<2, T> getSize() const {
                return size;
            }

            vector<2, T> getCenter() const {
                return position + size / 2;
            }

            vector<2, T> getTopLeft() const {
                return position;
            }

            vector<2, T> getTopRight() const {
                return {position.x + size.x, position.y};
            }

            vector<2, T> getBottomLeft() const {
                return {position.x, position.y + size.y};
            }

            vector<2, T> getBottomRight() const {
                return position + size;
            }

            T getLeft() const {
                return position.x;
            }

            T getRight() const {
                return position.x + size.x;
            }

            T getTop() const {
                return position.y;
            }

            T getBottom() const {
                return position.y + size.y;
            }

            T getHeight() const {
                return size.y;
            }

            T getWidth() const {
                return size.x;
            }
        };

}
