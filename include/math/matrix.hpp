
#pragma once

#include <type_traits>
#include <cstddef>
#include <ostream>

#include "vector.hpp"

namespace zephyr::math {

    template<size_t M, size_t N, typename T>
    requires std::is_arithmetic_v<T>
    class matrix {
        T _data[M][N] = {0};

        public:
            using type = T;

            constexpr size_t rows() const {
                return M;
            }

            constexpr size_t columns() const {
                return N;
            }

            constexpr matrix() {
                constexpr size_t min = M < N ? M : N;
                for (size_t i = 0; i < min; ++i) {
                    _data[i][i] = 1;
                }
            }
            
            // Copy&Move constructors

            constexpr matrix(const matrix<M, N, T> &other) = default;
            constexpr matrix(matrix<M, N, T> &&other) = default;

            // Conversion copy&move constructors

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix(const matrix<M, N, U> &other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        _data[i][j] = static_cast<T>(other._data[i][j]);
                    }
                }
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix(matrix<M, N, U> &&other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        _data[i][j] = static_cast<T>(other._data[i][j]);
                    }
                }
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix(const U (&arr)[M][N]) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        _data[i][j] = static_cast<T>(arr[i][j]);
                    }
                }
            }

            // Scalar constructor

            explicit constexpr matrix(T x) {
                for (size_t i = 0; i < M; ++i) {
                    _data[i][i] = x;
                }
            }

            template<typename... Ts>
            requires std::conjunction_v<std::is_convertible<Ts, T>...> && (sizeof...(Ts) == (M * N))
            explicit constexpr matrix(Ts... v) {
                T arr[] = {static_cast<T>(v)...};
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        _data[i][j] = arr[i * M + j];
                    }
                }
            }

            // Conversions from other matrix types

            template<size_t O, size_t P, typename U>
            requires std::is_convertible_v<U, T>
            explicit constexpr matrix(const matrix<O, P, U> &other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        if (i < O && j < P) {
                            _data[i][j] = other[i][j];
                        } else {
                            if constexpr (M == N) {
                                _data[i][j] = static_cast<T>(i == j);
                            } else {
                                _data[i][j] = static_cast<T>(0);
                            }
                        }
                    }
                }
            }

            // Assignments

            template<size_t O, size_t P, typename U>
            requires std::is_convertible_v<U, T> && (O > M) && (P > N)
            constexpr matrix<M, N, T> &operator=(const matrix<O, P, U> &other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] = other._data[i][j];
                    }
                }
                return *this;
            }

            template<size_t O, size_t P, typename U>
            requires std::is_convertible_v<U, T> && (O > M) && (P > N)
            constexpr matrix<M, N, T> &operator=(matrix<O, P, U> &&other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] = other._data[i][j];
                    }
                }
                return *this;
            }

            // Unary Scalar Arithmetic operators

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator+=(U x) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] += x;
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator+=(const matrix<M, N, U> &other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] += other[i][j];
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator-=(U x) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] -= x;
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator-=(const matrix<M, N, U> &other) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] -= other[i][j];
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator*=(U x) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] *= x;
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T> && (M == N)
            constexpr matrix<M, N, T> &operator*=(const matrix<M, N, U> &other) {
                matrix<M, N, T> temp = *this;
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; j++) {
                        this->_data[i][j] = 0;
                        for (size_t k = 0; k < M; ++k) {
                            this->_data[i][j] += temp[i][k] * other[k][j];
                        }
                    }
                }
                return *this;
            }

            template<typename U>
            requires std::is_convertible_v<U, T>
            constexpr matrix<M, N, T> &operator/=(U x) {
                for (size_t i = 0; i < M; ++i) {
                    for (size_t j = 0; j < N; ++j) {
                        this->_data[i][j] /= x;
                    }
                }
                return *this;
            }

            // Methods

            T *operator[](size_t i) {
                return _data[i];
            }

            const T *operator[](size_t i) const {
                return _data[i];
            }
    };

    // Unary Arithmetic operators

    template<size_t M, size_t N, typename T>
    constexpr matrix<M, N, T> operator+(const matrix<M, N, T> &mat) {
        return mat;
    }

    template<size_t M, size_t N, typename T>
    constexpr matrix<M, N, T> operator-(const matrix<M, N, T> &mat) {
        matrix<M, N, T> temp = mat;
        temp *= -1;
        return temp;
    }

    // Binary Scalar Arithmetic operators

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator+(const matrix<M, N, T> &mat, U x) {
        matrix<M, N, T> temp = mat;
        temp += x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator+(U x, const matrix<M, N, T> &mat) {
        matrix<M, N, T> temp = mat;
        temp += x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator-(const matrix<M, N, T> &mat, U x) {
        matrix<M, N, T> temp = mat;
        temp -= x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator-(U x, const matrix<M, N, T> &mat) {
        matrix<M, N, T> temp = -mat;
        temp += x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator*(const matrix<M, N, T> &mat, U x) {
        matrix<M, N, T> temp = mat;
        temp *= x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator*(U x, const matrix<M, N, T> &mat) {
        matrix<M, N, T> temp = mat;
        temp *= x;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator/(const matrix<M, N, T> &mat, U x) {
        matrix<M, N, T> temp = mat;
        temp /= x;
        return temp;
    }

    // Binary Matrix Arithmetic operators

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator+(const matrix<M, N, T> &lhs, const matrix<M, N, U> &rhs) {
        matrix<M, N, T> temp = lhs;
        temp += rhs;
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, N, T> operator-(const matrix<M, N, T> &lhs, const matrix<M, N, U> &rhs) {
        matrix<M, N, T> temp = lhs;
        temp -= rhs;
        return temp;
    }

    template<size_t M, size_t N, size_t P, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr matrix<M, P, T> operator*(const matrix<M, N, T> &lhs, const matrix<N, P, U> &rhs) {
        matrix<M, P, T> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < P; ++j) {
                temp[i][j] = 0;
                for (size_t k = 0; k < N; ++k) {
                    temp[i][j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        return temp;
    }

    // Binary Vector Arithmetic operators

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<M, T> operator*(const matrix<M, N, T> &mat, const vector<N, U> &vec) {
        vector<M, T> temp;
        for (size_t i = 0; i < M; ++i) {
            temp[i] = 0;
            for (size_t j = 0; j < N; ++j) {
                temp[i] += mat[i][j] * vec[j];
            }
        }
        return temp;
    }

    template<size_t M, size_t N, typename T, typename U>
    requires std::is_convertible_v<U, T>
    constexpr vector<N, T> operator*(const vector<M, U> &vec, const matrix<M, N, T> &mat) {
        vector<N, T> temp;
        for (size_t i = 0; i < N; ++i) {
            temp[i] = 0;
            for (size_t j = 0; j < M; ++j) {
                temp[i] += vec[j] * mat[j][i];
            }
        }
        return temp;
    }

    // Misc operations

    template<size_t M, size_t N, typename T>
    constexpr matrix<N, M, T> transpose(const matrix<M, N, T> &mat) {
        matrix<N, M, T> temp;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j < N; j++) {
                temp[j][i] = mat[i][j];
            }
        }
        return temp;
    }

    template<size_t M, size_t N, typename T>
    std::ostream &operator<<(std::ostream &s, const matrix<M, N, T> &mat) {
        for (size_t i = 0; i < M; ++i) {
            s << "[";
            for (size_t j = 0; j < N; ++j) {
                s << mat[i][j];
                if (j < N - 1) {
                    s << ", ";
                }
            }
            s << "]";
            if (i < M - 1)
                s << std::endl;
        }
        return s;
    }

}