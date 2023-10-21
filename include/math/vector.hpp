
#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <experimental/simd>
#include <cmath>
#include <cstring>

#include "vectormeta.hpp"

namespace zephyr::math {
    
    template<size_t N, typename T>
    requires std::is_arithmetic_v<T>
    class vector {
        T _data[N];

        template<typename Ts>
        requires std::is_arithmetic_v<Ts> && std::is_convertible_v<Ts, T>
        constexpr void _set(size_t offset, Ts v) {
            _data[offset] = static_cast<T>(v);
        }

        template<size_t M, typename Ts>
        requires std::is_convertible_v<Ts, T>
        constexpr void _set(size_t offset, const vector<M, Ts> &v) {
            const Ts *data = v.data();
            for (size_t i = 0; i < M; ++i) {
                _data[offset + i] = static_cast<T>(data[i]);
            }
        }

        public:
            using type = T;

            constexpr size_t size() const {
                return N;
            }

            constexpr vector() = default;

            // Copy&move constructors

            constexpr vector(const vector<N, T> &other) = default;
            constexpr vector(vector<N, T> &&other) = default;

            // Conversion copy&move constructors

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(const vector<N, U> &other) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = static_cast<T>(other._data[i]);
                }
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(vector<N, U> &&other) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = static_cast<T>(other._data[i]);
                }
            }

            // Scalar constructor

            explicit constexpr vector(T x) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = x;
                }
            }

            template<typename... Ts>
            requires std::conjunction_v<std::is_same<Ts, T>...> && (sizeof...(Ts) == N)
            explicit constexpr vector(Ts... v) : _data{v...} {}

            template<typename... Vs>
            requires (_meta::argumentSize<std::remove_cvref_t<Vs>...>::value == N) && std::negation_v<std::conjunction<std::is_same<std::remove_cvref_t<Vs>, T>...>>
            explicit constexpr vector(Vs&&... v) {
                size_t off = 0;
                ([&] {
                    _set(off, std::forward<Vs>(v));
                    off += _meta::argumentSize<std::remove_cvref_t<Vs>>::value;
                }(), ...);
            }

            // Conversions from other vector types

            template<size_t M, typename U>
            requires std::is_convertible_v<U, T> && (M > N)
            explicit constexpr vector(const vector<M, U> &other) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = static_cast<T>(other._data[i]);
                }
            }

            // Assignments

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator=(const vector<N, U> &other) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = static_cast<T>(other._data[i]);
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator=(vector<N, U> &&other) {
                for (size_t i = 0; i < N; ++i) {
                    _data[i] = static_cast<T>(other._data[i]);
                }
                return *this;
            }

            // Unary Scalar Arithmetic operators

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator+=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
                a += b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator-=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
                a -= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator*=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
                a *= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator/=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
                a /= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<N, T> &operator%=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
                a %= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            // Bitwise operators

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<N, T> &operator&=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, N> b(scalar);
                a &= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<N, T> &operator|=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, N> b(scalar);
                a |= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<N, T> &operator^=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, N> b(scalar);
                a ^= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<N, T> &operator<<=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, N> b(scalar);
                a <<= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<N, T> &operator>>=(U scalar) {
                std::experimental::fixed_size_simd<T, N> a(this->data(), std::experimental::vector_aligned);
                const std::experimental::fixed_size_simd<U, N> b(scalar);
                a >>= b;
                a.copy_to(this->data(), std::experimental::vector_aligned);
                return *this;
            }

            constexpr T dot(const vector<N, T> &other) const;

            double length() const {
                return std::sqrt(this->dot(*this));
            }

            double angle(const vector<N, T> &other) const {
                return std::acos(this->dot(other) / (this->length() * other.length()));
            }

            vector<N, T> unit() const {
                return *this / this->length();
            }

            T scalarProject(const vector<N, T> &other) const {
                return this->dot(other.unit());
            }

            constexpr T *data() {
                return this->_data;
            }

            constexpr const T *data() const {
                return this->_data;
            }
    };

} // namespace zephyr::math

#include "vector.inl"
