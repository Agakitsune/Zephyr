
#pragma once

#include <type_traits>

#include "math/vector.hpp"

namespace zephyr::math {
    
    template<typename T>
    requires std::is_arithmetic_v<T>
    class vector<1, T> {
        public:
            using type = T;

            union {
                T x;
                T r;
                T s;
            };

            constexpr size_t size() const {
                return 1;
            }

            constexpr vector() = default;

            // Copy&move constructors

            constexpr vector(const vector<1, T> &other) = default;
            constexpr vector(vector<1, T> &&other) = default;

            // Conversion copy&move constructors

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(const vector<1, U> &other) : x(static_cast<T>(other.x)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector(vector<1, U> &&other) : x(static_cast<T>(other.x)) {}

            // Scalar constructor

            explicit constexpr vector(T x) : x(x) {}

            // Conversions from other vector types

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<2, U> &other) : x(static_cast<T>(other.x)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<3, U> &other) : x(static_cast<T>(other.x)) {}

            template<typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr vector(const vector<4, U> &other) : x(static_cast<T>(other.x)) {}

            // Assignments

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator=(const vector<1, U> &other) {
                this->x = static_cast<T>(other.x);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator=(vector<1, U> &&other) {
                this->x = static_cast<T>(other.x);
                return *this;
            }

            // Unary Scalar Arithmetic operators

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator+=(U scalar) {
                this->x += static_cast<T>(scalar);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator-=(U scalar) {
                this->x -= static_cast<T>(scalar);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator*=(U scalar) {
                this->x *= static_cast<T>(scalar);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator/=(U scalar) {
                this->x /= static_cast<T>(scalar);
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr vector<1, T> &operator%=(U scalar) {
                this->x %= static_cast<T>(scalar);
                return *this;
            }

            // Bitwise operators

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<1, T> &operator&=(U scalar) {
                this->x &= scalar;
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<1, T> &operator|=(U scalar) {
                this->x |= scalar;
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<1, T> &operator^=(U scalar) {
                this->x ^= scalar;
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<1, T> &operator<<=(U scalar) {
                this->x <<= scalar;
                return *this;
            }

            template<typename U>
            requires std::is_integral_v<U>
            constexpr vector<1, T> &operator>>=(U scalar) {
                this->x >>= scalar;
                return *this;
            }

            constexpr T dot(const vector<1, T> &other) const;

            double length() const {
                return std::sqrt(this->dot(*this));
            }

            vector<1, T> unit() const {
                return *this / this->length();
            }

            constexpr T *data() {
                return &this->x;
            }

            constexpr const T *data() const {
                return &this->x;
            }
    };

    // Unary arithmetic operators

    template<typename T>
    constexpr vector<1, T> operator+(const vector<1, T> &vec) {
        return vec;
    }

    template<typename T>
    constexpr vector<1, T> operator-(const vector<1, T> &vec) {
        return vector<1, T>(-vec.x);
    }

    // Binary arithmetic operators

    template<typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<1, T> operator+(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x + static_cast<T>(scalar));
    }

    template<typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<1, T> operator-(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x - static_cast<T>(scalar));
    }

    template<typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<1, T> operator*(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x * static_cast<T>(scalar));
    }

    template<typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<1, T> operator/(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x / static_cast<T>(scalar));
    }

    template<typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<1, T> operator%(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x % static_cast<T>(scalar));
    }

    // Bitwise operators

    template<typename T, typename U>
    requires std::is_integral_v<U>
    constexpr vector<1, T> operator&(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x & scalar);
    }

    template<typename T, typename U>
    requires std::is_integral_v<U>
    constexpr vector<1, T> operator|(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x | scalar);
    }

    template<typename T, typename U>
    requires std::is_integral_v<U>
    constexpr vector<1, T> operator^(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x ^ scalar);
    }

    template<typename T, typename U>
    requires std::is_integral_v<U>
    constexpr vector<1, T> operator<<(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x << scalar);
    }

    template<typename T, typename U>
    requires std::is_integral_v<U>
    constexpr vector<1, T> operator>>(const vector<1, T> &vec, U scalar) {
        return vector<1, T>(vec.x >> scalar);
    }

    template<typename T>
    requires std::is_integral_v<T>
    constexpr vector<1, T> operator~(const vector<1, T> &vec) {
        return vector<1, T>(~vec.x);
    }

    // Equality operators

    template<typename T>
    requires std::equality_comparable<T>
    constexpr bool operator==(const vector<1, T> &lhs, const vector<1, T> &rhs) {
        return lhs.x == rhs.x;
    }

    template<typename T>
    requires std::equality_comparable<T>
    constexpr bool operator!=(const vector<1, T> &lhs, const vector<1, T> &rhs) {
        return lhs.x != rhs.x;
    }

    // Vector arithmetic operators

    template<typename T>
    constexpr vector<1, T> operator+(const vector<1, T> &lhs, const vector<1, T> &rhs) {
        return vector<1, T>(lhs.x + rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator-(const vector<1, T> &lhs, const vector<1, T> &rhs) {
        return vector<1, T>(lhs.x - rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator*(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x * rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator/(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x / rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator%(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x % rhs.x);
    }

    // Bitwise operators

    template<typename T>
    constexpr vector<1, T> operator&(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x & rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator|(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x | rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator^(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x ^ rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator<<(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x << rhs.x);
    }

    template<typename T>
    constexpr vector<1, T> operator>>(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return vector<1, T>(lhs.x >> rhs.x);
    }

    // Vector operations

    template<typename T>
    constexpr T dot(const vector<1, T> &lhs, const vector<1, T> &rhs)  {
        return lhs.x * rhs.x;
    }

} // namespace zephyr::math

#include "vector1.inl"
