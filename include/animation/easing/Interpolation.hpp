
#pragma once

#include <type_traits>

#include "Easing.hpp"

#include "math/vector.hpp"

namespace zephyr::animation {
    
    template<typename T>
    class Interpolation;

    template<typename T>
    requires std::is_arithmetic_v<T>
    class Interpolation<T> {
        Easing easing;
        T start;
        T end;

        public:
            Interpolation() = default;

            void interpolate(const std::function<float(float)> &ease, T start, T end, int step = 32) {
                easing = Easing(ease, step);
                this->start = start;
                this->end = end;
            }

            T current() {
                float t = easing.current();
                return (1 - t) * start + t * end;
            }

            T next() {
                float next = easing.next();
                return (1 - next) * start + next * end;
            }

            bool finished() const {
                return easing.finished();
            }

            void reset() {
                easing.reset();
            }
    };

    template<size_t N, typename T>
    requires std::is_arithmetic_v<T>
    class Interpolation<math::vector<N, T>> {
        Easing easing;
        math::vector<N, T> start;
        math::vector<N, T> end;

        public:
            Interpolation() = default;

            void interpolate(const std::function<float(float)> &ease, const math::vector<N, T>& start, const math::vector<N, T>& end, int step = 32) {
                easing = Easing(ease, step);
                this->start = start;
                this->end = end;
            }

            math::vector<N, T> current() {
                float t = easing.current();
                return (1 - t) * start + t * end;
            }

            math::vector<N, T> next() {
                float next = easing.next();
                return (1 - next) * start + next * end;
            }

            bool finished() const {
                return easing.finished();
            }

            void reset() {
                easing.reset();
            }
    };

} // namespace zephyr::animation
