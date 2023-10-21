
#pragma once

#include <iostream>
#include <experimental/simd>
#include <type_traits>

#include "vector.hpp"

namespace zephyr::math {

    template<typename T, size_t N>
    constexpr vector<N, T> operator+(const vector<N, T> &vec) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        return vector<N, T>(+a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator-(const vector<N, T> &vec) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        return vector<N, T>(-a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator+(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
        a += b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator-(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
        a -= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator*(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
        a *= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator/(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
        a /= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator%(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(static_cast<T>(scalar));
        a %= b;
        return vector<N, T>(a);
    }

    // Bitwise operators

    template<typename T, typename U, size_t N>
    requires std::is_integral_v<U>
    constexpr vector<N, T> operator&(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<U, N> b(scalar);
        a &= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_integral_v<U>
    constexpr vector<N, T> operator|(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<U, N> b(scalar);
        a |= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_integral_v<U>
    constexpr vector<N, T> operator^(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<U, N> b(scalar);
        a ^= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_integral_v<U>
    constexpr vector<N, T> operator<<(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<U, N> b(scalar);
        a <<= b;
        return vector<N, T>(a);
    }

    template<typename T, typename U, size_t N>
    requires std::is_integral_v<U>
    constexpr vector<N, T> operator>>(const vector<N, T> &vec, U scalar) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<U, N> b(scalar);
        a >>= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    requires std::is_integral_v<T>
    constexpr vector<N, T> operator~(const vector<N, T> &vec) {
        std::experimental::fixed_size_simd<T, N> a(vec.data(), std::experimental::vector_aligned);
        return vector<N, T>(~a);
    }

    // Equality operators

    template<typename T, size_t N>
    requires std::equality_comparable<T>
    constexpr bool operator==(const vector<N, T> &lhs, const vector<N, T> &rhs) {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        return std::experimental::all_of(a == b);
    }

    template<typename T, size_t N>
    requires std::equality_comparable<T>
    constexpr bool operator!=(const vector<N, T> &lhs, const vector<N, T> &rhs) {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        return std::experimental::all_of(a != b);
    }

    // Vector arithmetic operators

    template<typename T, size_t N>
    constexpr vector<N, T> operator+(const vector<N, T> &lhs, const vector<N, T> &rhs) {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a += b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator-(const vector<N, T> &lhs, const vector<N, T> &rhs) {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a -= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator*(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a *= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator/(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a /= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator%(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a %= b;
        return vector<N, T>(a);
    }

    // Bitwise operators

    template<typename T, size_t N>
    constexpr vector<N, T> operator&(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a &= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator|(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a |= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator^(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a ^= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator<<(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a <<= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    constexpr vector<N, T> operator>>(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a >>= b;
        return vector<N, T>(a);
    }

    template<typename T, size_t N>
    requires std::is_arithmetic_v<T>
    constexpr T dot(const vector<N, T> &lhs, const vector<N, T> &rhs)  {
        std::experimental::fixed_size_simd<T, N> a(lhs.data(), std::experimental::vector_aligned);
        const std::experimental::fixed_size_simd<T, N> b(rhs.data(), std::experimental::vector_aligned);
        a *= b;
        return std::experimental::reduce(a);
    }

    template<typename T, size_t N>
    std::ostream &operator<<(std::ostream &s, const vector<N, T> &vec) {
        const T *data = vec.data();
        s << '[';
        for (size_t i = 0; i < N; ++i) {
            s << data[i];
            if (i < N - 1) {
                s << ", ";
            }
        }
        return s << ']';
    }

} // namespace zephyr::math
