
#pragma once

#include <experimental/simd>
#include <type_traits>

#include "math/vector.hpp"

namespace zephyr::math {
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    class vector<2, T> {
        public:
            using type = T;

            union {
                struct {
                    T x;
                    T y;
                };
                struct {
                    T r;
                    T g;
                };
                struct {
                    T s;
                    T t;
                };
            };

            constexpr size_t size() const {
                return 2;
            }

            constexpr vector() = default;

            template<typename A>
            constexpr vector(std::experimental::simd<T, A> value) : x(value[0]), y(value[1]) {}

            // Copy&move constructors

            constexpr vector(const vector<2, T> &other) = default;
            constexpr vector(vector<2, T> &&other) = default;

            // Conversion copy&move constructors

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(const vector<2, U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(vector<2, U> &&other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

            // Scalar constructor

            explicit constexpr vector(T x) : x(x), y(x) {}
            explicit constexpr vector(T x, T y) : x(x), y(y) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<1, U> &x, T y) : x(static_cast<T>(x.x)), y(y) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, const vector<1, U> &y) : x(x), y(static_cast<T>(y.x)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, U> &x, const vector<1, V> &y) : x(static_cast<T>(x.x)), y(static_cast<T>(y.x)) {}

            // Conversions from other vector types

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<3, U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<4, U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}

            // Assignments

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator=(const vector<2, U> &other) {
                this->x = static_cast<T>(other.x);
                this->y = static_cast<T>(other.y);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator=(vector<2, U> &&other) {
                this->x = static_cast<T>(other.x);
                this->y = static_cast<T>(other.y);
                return *this;
            }

            // Unary Scalar Arithmetic operators

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator+=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 2> b(static_cast<T>(scalar));
                a += b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator-=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 2> b(static_cast<T>(scalar));
                a -= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator*=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 2> b(static_cast<T>(scalar));
                a *= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator/=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 2> b(static_cast<T>(scalar));
                a /= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<2, T> &operator%=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 2> b(static_cast<T>(scalar));
                a %= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            // Bitwise operators

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<2, T> &operator&=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 2> b(scalar);
                a &= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<2, T> &operator|=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 2> b(scalar);
                a |= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<2, T> &operator^=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 2> b(scalar);
                a ^= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<2, T> &operator<<=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 2> b(scalar);
                a <<= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<2, T> &operator>>=(U scalar) {
                std::experimental::fixed_size_simd<T, 2> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 2> b(scalar);
                a >>= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            constexpr T dot(const vector<2, T> &other) const;

            double length() const {
                return std::sqrt(this->dot(*this));
            }

            double angle(const vector<2, T> &other) const {
                return std::acos(this->dot(other) / (this->length() * other.length()));
            }

            vector<2, T> unit() const {
                return *this / this->length();
            }

            T scalarProject(const vector<2, T> &other) const {
                return this->dot(other.unit());
            }

            constexpr T *data() {
                return &this->x;
            }

            constexpr const T *data() const {
                return &this->x;
            }
    };

} // namespace zephyr::math

#include "vector2.inl"
