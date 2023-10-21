
#pragma once

#include <experimental/simd>
#include <type_traits>

#include "math/vector.hpp"

namespace zephyr::math {
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    class vector<4, T> {
        public:
            using type = T;

            union {
                struct {
                    T x;
                    T y;
                    T z;
                    T w;
                };
                struct {
                    T r;
                    T g;
                    T b;
                    T a;
                };
                struct {
                    T s;
                    T t;
                    T p;
                    T q;
                };
            };

            constexpr size_t size() const {
                return 4;
            }

            constexpr vector() = default;

            template<typename A>
            constexpr vector(std::experimental::simd<T, A> value) : x(value[0]), y(value[1]) {}

            // Copy&move constructors

            constexpr vector(const vector<4, T> &other) = default;
            constexpr vector(vector<4, T> &&other) = default;

            // Conversion copy&move constructors

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(const vector<4, U> &other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(vector<4, U> &&other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)), w(static_cast<T>(other.w)) {}

            // Scalar constructor

            explicit constexpr vector(T x) : x(x), y(x), z(x), w(x) {}
            explicit constexpr vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<1, U> &x, T y, T z, T w) : x(static_cast<T>(x.x)), y(y), z(z), w(w) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, const vector<1, U> &y, T z, T w) : x(x), y(static_cast<T>(y.y)), z(z), w(w) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, T y, const vector<1, U> &z, T w) : x(x), y(y), z(static_cast<T>(z.z)), w(w) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, T y, T z, const vector<1, U> &w) : x(x), y(y), z(z), w(static_cast<T>(w.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, U> &x, const vector<1, U> &y, T z, T w) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(z), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, U> &x, T y, const vector<1, U> &z, T w) : x(static_cast<T>(x.x)), y(y), z(static_cast<T>(z.z)), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, U> &x, T y, T z, const vector<1, V> &w) : x(static_cast<T>(x.x)), y(y), z(z), w(static_cast<T>(w.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(T x, const vector<1, U> &y, const vector<1, V> &z, T w) : x(x), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(T x, const vector<1, U> &y, T z, const vector<1, V> &w) : x(x), y(static_cast<T>(y.y)), z(z), w(static_cast<T>(w.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(T x, T y, const vector<1, U> &z, const vector<1, V> &w) : x(x), y(y), z(static_cast<T>(z.z)), w(static_cast<T>(w.w)) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<1, U> &x, const vector<1, V> &y, const vector<1, W> &z, T w) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(w) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<1, U> &x, const vector<1, V> &y, T z, const vector<1, W> &w) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(z), w(static_cast<T>(w.w)) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<1, U> &x, T y, const vector<1, V> &z, const vector<1, W> &w) : x(static_cast<T>(x.x)), y(y), z(static_cast<T>(z.z)), w(static_cast<T>(w.w)) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(T x, const vector<1, U> &y, const vector<1, V> &z, const vector<1, W> &w) : x(x), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(static_cast<T>(w.w)) {}

            template<typename U, typename V, typename W, typename X>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T> && std::is_convertible_v<X, T>
            explicit constexpr vector(const vector<1, U> &x, const vector<1, V> &y, const vector<1, W> &z, const vector<1, X> &w) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(static_cast<T>(w.w)) {}


            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<2, U> &xy, T z, T w) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(z), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<2, U> &xy, const vector<1, V> &z, T w) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(static_cast<T>(z.z)), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<2, U> &xy, T z, const vector<1, V> &w) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(z), w(static_cast<T>(w.w)) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<2, U> &xy, const vector<1, V> &z, const vector<1, W> &w) : x(static_cast<T>(x.x)), y(static_cast<T>(x.y)), z(static_cast<T>(z.z)), w(static_cast<T>(w.w)) {}


            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, const vector<2, U> &yz, T w) : x(x), y(static_cast<T>(y.y)), z(static_cast<T>(y.z)), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(T x, const vector<2, U> &yz, const vector<1, V> &w) : x(x), y(static_cast<T>(y.y)), z(static_cast<T>(y.z)), w(static_cast<T>(w.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, V> &x, const vector<2, U> &yz, T w) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(static_cast<T>(y.z)), w(w) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<1, V> &x, const vector<2, U> &yz, const vector<1, W> &w) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(static_cast<T>(y.z)), w(static_cast<T>(w.w)) {}


            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, T y, const vector<2, U> &zw) : x(x), y(y), z(static_cast<T>(z.z)), w(static_cast<T>(z.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, V> &x, T y, const vector<2, U> &zw) : x(static_cast<T>(x.x)), y(y), z(static_cast<T>(z.z)), w(static_cast<T>(z.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(T x, const vector<1, V> &y, const vector<2, U> &zw) : x(x), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(static_cast<T>(z.w)) {}

            template<typename U, typename V, typename W>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T> && std::is_convertible_v<W, T>
            explicit constexpr vector(const vector<1, V> &x, const vector<1, V> &y, const vector<2, U> &zw) : x(static_cast<T>(x.x)), y(static_cast<T>(y.y)), z(static_cast<T>(z.z)), w(static_cast<T>(z.w)) {}


            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<3, U> &xyz, T w) : x(static_cast<T>(xyz.x)), y(static_cast<T>(xyz.y)), z(static_cast<T>(xyz.z)), w(w) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<3, U> &xyz, const vector<1, V> &w) : x(static_cast<T>(xyz.x)), y(static_cast<T>(xyz.y)), z(static_cast<T>(xyz.z)), w(static_cast<T>(w.w)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(T x, const vector<3, U> &yzw) : x(x), y(static_cast<T>(yzw.y)), z(static_cast<T>(yzw.z)), w(static_cast<T>(yzw.w)) {}

            template<typename U, typename V>
            requires std::is_convertible_v<U, T> && std::is_convertible_v<V, T>
            explicit constexpr vector(const vector<1, V> &x, const vector<3, U> &yzw) : x(static_cast<T>(x.x)), y(static_cast<T>(yzw.y)), z(static_cast<T>(yzw.z)), w(static_cast<T>(yzw.w)) {}

            // Assignments

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator=(const vector<4, U> &other) {
                this->x = static_cast<T>(other.x);
                this->y = static_cast<T>(other.y);
                this->z = static_cast<T>(other.z);
                this->w = static_cast<T>(other.w);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator=(vector<4, U> &&other) {
                this->x = static_cast<T>(other.x);
                this->y = static_cast<T>(other.y);
                this->z = static_cast<T>(other.z);
                this->w = static_cast<T>(other.w);
                return *this;
            }

            // Unary Scalar Arithmetic operators

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator+=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 4> b(static_cast<T>(scalar));
                a += b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator-=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 4> b(static_cast<T>(scalar));
                a -= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator*=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 4> b(static_cast<T>(scalar));
                a *= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator/=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 4> b(static_cast<T>(scalar));
                a /= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<4, T> &operator%=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, 4> b(static_cast<T>(scalar));
                a %= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            // Bitwise operators

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<4, T> &operator&=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 4> b(scalar);
                a &= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<4, T> &operator|=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 4> b(scalar);
                a |= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<4, T> &operator^=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 4> b(scalar);
                a ^= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<4, T> &operator<<=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 4> b(scalar);
                a <<= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<4, T> &operator>>=(U scalar) {
                std::experimental::fixed_size_simd<T, 4> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, 4> b(scalar);
                a >>= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            constexpr T dot(const vector<4, T> &other) const;

            double length() const {
                return std::sqrt(this->dot(*this));
            }

            double angle(const vector<4, T> &other) const {
                return std::acos(this->dot(other) / (this->length() * other.length()));
            }

            vector<4, T> unit() const {
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

#include "vector4.inl"
