
#pragma once

#include <type_traits>
#include <vector>

#include "gl/VertexArray.hpp"

#include "math/math.hpp"

namespace zephyr::utils {

    template<typename T>
    class VertexData {
        std::vector<T> _data;

        public:
            VertexData() = default;

            void push(T unit) {
                _data.push_back(unit);
            }
            
            void push2(T unit1, T unit2) {
                _data.push_back(unit1);
                _data.push_back(unit2);
            }

            void push3(T unit1, T unit2, T unit3) {
                _data.push_back(unit1);
                _data.push_back(unit2);
                _data.push_back(unit3);
            }

            void push4(T unit1, T unit2, T unit3, T unit4) {
                _data.push_back(unit1);
                _data.push_back(unit2);
                _data.push_back(unit3);
                _data.push_back(unit4);
            }

            template<size_t N, typename T2>
            requires std::is_convertible_v<T2, T>
            void push(const math::vector<N, T2> &unit) {
                for (size_t i = 0; i < N; i++) {
                    _data.push_back(unit[i]);
                }
            }

            constexpr size_t size() const noexcept {
                return _data.size();
            }

            constexpr size_t bufferSize() const noexcept {
                return _data.size() * sizeof(T);
            }

            constexpr const T *data() const noexcept {
                return _data.data();
            }
    };

} // namespace zephyr::utils
