
#pragma once

#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <type_traits>

namespace zephyr::math {
    
    template<size_t N, typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class vector {
        T _data[N];

        public:
            vector() = default;
            vector(const vector<N, T> &other) = default;
            vector(vector<N, T> &&other) = default;

            vector<N, T> &operator=(const vector<N, T> &other) = default;
            vector<N, T> &operator=(vector<N, T> &&other) = default;

            T &operator[](size_t index) {
                return _data[index];
            }

            const T &operator[](size_t index) const {
                return _data[index];
            }

            T *begin() {
                return _data;
            }

            const T *begin() const {
                return _data;
            }

            T *end() {
                return _data + N;
            }

            const T *end() const {
                return _data + N;
            }

            T *data() {
                return _data;
            }

            const T *data() const {
                return _data;
            }

            constexpr size_t size() const noexcept {
                return N;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class dynamic_vector {
        T *_data;
        size_t n;

        public:
            dynamic_vector(size_t n) : n(n) {
                this->_data = new T[n];
            }

            template<size_t N>
            dynamic_vector(const vector<N, T> &other) {
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
            }

            template<size_t N>
            dynamic_vector(vector<N, T> &&other) {
                this->n = other.n;
                this->_data = other._data;
            }

            dynamic_vector(const dynamic_vector<T> &other) {
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
            }

            dynamic_vector(dynamic_vector<T> &&other) {
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
            }

            ~dynamic_vector() {
                if (this->_data != nullptr) {
                    delete[] this->_data;
                }
            }

            template<size_t N>
            vector<N, T> &operator=(const vector<N, T> &other) {
                if (this->_data != nullptr) {
                    delete[] this->_data;
                }
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
                return *this;
            }

            template<size_t N>
            vector<N, T> &operator=(vector<N, T> &&other) {
                if (this->_data != nullptr) {
                    delete[] this->_data;
                }
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
                return *this;
            }

            dynamic_vector<T> &operator=(const dynamic_vector<T> &other) {
                if (this->_data != nullptr) {
                    delete[] this->_data;
                }
                this->n = other.n;
                this->_data = new T[n];
                std::memcpy(this->_data, other._data, n * sizeof(T));
                return *this;
            }

            dynamic_vector<T> &operator=(dynamic_vector<T> &&other) {
                if (this->_data != nullptr) {
                    delete[] this->_data;
                }
                this->n = other.n;
                this->_data = other._data;
                other._data = nullptr;
                return *this;
            }

            T &operator[](size_t index) {
                return _data[index];
            }

            const T &operator[](size_t index) const {
                return _data[index];
            }

            T *begin() {
                return _data;
            }

            const T *begin() const {
                return _data;
            }

            T *end() {
                return _data + n;
            }

            const T *end() const {
                return _data + n;
            }

            T *data() {
                return _data;
            }

            const T *data() const {
                return _data;
            }

            size_t size() const noexcept {
                return n;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class vector<1, T> {
        public:
            union {
                T x;
                T r;
            };

            vector() = default;
            vector(T x) : x(x) {}
            vector(const vector<1, T> &other) = default;
            vector(vector<1, T> &&other) = default;

            vector<1, T> &operator=(const vector<1, T> &other) = default;
            vector<1, T> &operator=(vector<1, T> &&other) = default;

            T &operator[](size_t index) {
                if (index == 0) {
                    return x;
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            const T &operator[](size_t index) const {
                if (index == 0) {
                    return x;
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            T *begin() {
                return &x;
            }

            const T *begin() const {
                return &x;
            }

            T *end() {
                return (&x) + 1;
            }

            const T *end() const {
                return (&x) + 1;
            }

            T *data() {
                return &x;
            }

            const T *data() const {
                return &x;
            }

            constexpr size_t size() const {
                return 1;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class vector<2, T> {
        public:
            union {
                T _data[2];
                struct {
                    T x;
                    T y;
                };
                struct {
                    T r;
                    T g;
                };
                struct {
                    T width;
                    T height;
                };
            };

            vector() = default;

            vector(T value) : x(value), y(value) {}
            vector(T x, T y) : x(x), y(y) {}

            vector(const vector<1, T> &value) : x(value.x), y(value.x) {}
            vector(const vector<1, T> &x, const vector<1, T> &y) : x(x.x), y(y.x) {}

            vector(const vector<2, T> &other) = default;
            vector(vector<2, T> &&other) = default;

            vector<2, T> &operator=(const vector<2, T> &other) = default;
            vector<2, T> &operator=(vector<2, T> &&other) = default;

            T &operator[](size_t index) {
                if (index < 2) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            const T &operator[](size_t index) const {
                if (index < 2) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            T *begin() {
                return _data;
            }

            const T *begin() const {
                return _data;
            }

            T *end() {
                return _data + 2;
            }

            const T *end() const {
                return _data + 2;
            }

            T *data() {
                return _data;
            }

            const T *data() const {
                return _data;
            }

            constexpr size_t size() const {
                return 2;
            }

            template<size_t K>
            requires (K <= 2)
            vector<K, T> swizzle(const std::string &swizzle) const {
                vector<K, T> result;
                for (size_t i = 0; i < K; i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }

            dynamic_vector<T> swizzle(const std::string &swizzle) const {
                dynamic_vector<T> result(swizzle.size());
                for (size_t i = 0; i < swizzle.size(); i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class vector<3, T> {
        public:
            union {
                T _data[3];
                struct {
                    T x;
                    T y;
                    T z;
                };
                struct {
                    T r;
                    T g;
                    T b;
                };
                struct {
                    T width;
                    T height;
                    T depth;
                };
            };

            vector() = default;
            vector(T value) : x(value), y(value), z(value) {}
            vector(T x, T y, T z) : x(x), y(y), z(z) {}
            
            vector(const vector<1, T> &value) : x(value.x), y(value.x), z(value.x) {}
            vector(const vector<1, T> &x, const vector<1, T> &y, const vector<1, T> &z) : x(x.x), y(y.x), z(z.x) {}
            vector(const vector<2, T> &value, const vector<1, T> &z) : x(value.x), y(value.y), z(z.x) {}
            vector(const vector<1, T> &x, const vector<2, T> &value) : x(x.x), y(value.x), z(value.y) {}
            
            vector(const vector<3, T> &other) = default;
            vector(vector<3, T> &&other) = default;

            vector<3, T> &operator=(const vector<3, T> &other) = default;
            vector<3, T> &operator=(vector<3, T> &&other) = default;

            T &operator[](size_t index) {
                if (index < 3) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            const T &operator[](size_t index) const {
                if (index < 3) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            T *begin() {
                return _data;
            }

            const T *begin() const {
                return _data;
            }

            T *end() {
                return _data + 3;
            }

            const T *end() const {
                return _data + 3;
            }

            T *data() {
                return _data;
            }

            const T *data() const {
                return _data;
            }

            constexpr size_t size() const {
                return 3;
            }

            template<size_t K>
            requires (K <= 2)
            vector<K, T> swizzle(const std::string &swizzle) const {
                vector<K, T> result;
                for (size_t i = 0; i < K; i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'z':
                            result[i] = z;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        case 'b':
                            result[i] = b;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }

            dynamic_vector<T> swizzle(const std::string &swizzle) const {
                dynamic_vector<T> result(swizzle.size());
                for (size_t i = 0; i < swizzle.size(); i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'z':
                            result[i] = z;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        case 'b':
                            result[i] = b;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    class vector<4, T> {
        public:
            union {
                T _data[4];
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
            };

            vector() = default;
            vector(T value) : x(value), y(value), z(value) {}
            vector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
            
            vector(const vector<1, T> &value) : x(value.x), y(value.x), z(value.x), w(value.x) {}
            vector(const vector<1, T> &x, const vector<1, T> &y, const vector<1, T> &z, const vector<1, T> &w) : x(x.x), y(y.x), z(z.x), w(w.x) {}
            vector(const vector<2, T> &value, const vector<1, T> &z, const vector<1, T> &w) : x(value.x), y(value.y), z(z.x), w(w.x) {}
            vector(const vector<1, T> &x, const vector<2, T> &value, const vector<1, T> &w) : x(x.x), y(value.x), z(value.y), w(w.x) {}
            vector(const vector<1, T> &x, const vector<1, T> &y, const vector<2, T> &value) : x(x.x), y(y.x), z(value.x), w(value.y) {}
            vector(const vector<2, T> &value1, const vector<2, T> &value2) : x(value1.x), y(value1.y), z(value2.x), w(value2.y) {}
            vector(const vector<3, T> &value, const vector<1, T> &w) : x(value.x), y(value.y), z(value.z), w(w.x) {}
            vector(const vector<1, T> &x, const vector<3, T> &value) : x(x.x), y(value.x), z(value.y), w(value.z) {}
            
            vector(const vector<4, T> &other) = default;
            vector(vector<4, T> &&other) = default;

            vector<4, T> &operator=(const vector<4, T> &other) = default;
            vector<4, T> &operator=(vector<4, T> &&other) = default;

            T &operator[](size_t index) {
                if (index < 4) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            const T &operator[](size_t index) const {
                if (index < 4) {
                    return _data[index];
                } else {
                    throw std::out_of_range("Index out of range");
                }
            }

            T *begin() {
                return _data;
            }

            const T *begin() const {
                return _data;
            }

            T *end() {
                return _data + 4;
            }

            const T *end() const {
                return _data + 4;
            }

            T *data() {
                return _data;
            }

            const T *data() const {
                return _data;
            }

            constexpr size_t size() const {
                return 4;
            }

            template<size_t K>
            requires (K <= 2)
            vector<K, T> swizzle(const std::string &swizzle) const {
                vector<K, T> result;
                for (size_t i = 0; i < K; i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'z':
                            result[i] = z;
                            break;
                        case 'w':
                            result[i] = w;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        case 'b':
                            result[i] = b;
                            break;
                        case 'a':
                            result[i] = a;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }

            dynamic_vector<T> swizzle(const std::string &swizzle) const {
                dynamic_vector<T> result(swizzle.size());
                for (size_t i = 0; i < swizzle.size(); i++) {
                    switch (swizzle[i]) {
                        case 'x':
                            result[i] = x;
                            break;
                        case 'y':
                            result[i] = y;
                            break;
                        case 'z':
                            result[i] = z;
                            break;
                        case 'w':
                            result[i] = w;
                            break;
                        case 'r':
                            result[i] = r;
                            break;
                        case 'g':
                            result[i] = g;
                            break;
                        case 'b':
                            result[i] = b;
                            break;
                        case 'a':
                            result[i] = a;
                            break;
                        default:
                            throw std::invalid_argument("Invalid swizzle");
                    }
                }
                return result;
            }
    };

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    using vec1 = vector<1, T>;

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    using vec2 = vector<2, T>;

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    using vec3 = vector<3, T>;

    template<typename T>
    requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
    using vec4 = vector<4, T>;

    using vec1i = vec1<int>;
    using vec2i = vec2<int>;
    using vec3i = vec3<int>;
    using vec4i = vec4<int>;

    using vec1u = vec1<unsigned int>;
    using vec2u = vec2<unsigned int>;
    using vec3u = vec3<unsigned int>;
    using vec4u = vec4<unsigned int>;

    using vec1f = vec1<float>;
    using vec2f = vec2<float>;
    using vec3f = vec3<float>;
    using vec4f = vec4<float>;

    using vec1d = vec1<double>;
    using vec2d = vec2<double>;
    using vec3d = vec3<double>;
    using vec4d = vec4<double>;

    using vec1b = vec1<bool>;
    using vec2b = vec2<bool>;
    using vec3b = vec3<bool>;
    using vec4b = vec4<bool>;

    using vec1c = vec1<char>;
    using vec2c = vec2<char>;
    using vec3c = vec3<char>;
    using vec4c = vec4<char>;

    using vec1uc = vec1<unsigned char>;
    using vec2uc = vec2<unsigned char>;
    using vec3uc = vec3<unsigned char>;
    using vec4uc = vec4<unsigned char>;

    using vec1s = vec1<short>;
    using vec2s = vec2<short>;
    using vec3s = vec3<short>;
    using vec4s = vec4<short>;

    using vec1us = vec1<unsigned short>;
    using vec2us = vec2<unsigned short>;
    using vec3us = vec3<unsigned short>;
    using vec4us = vec4<unsigned short>;

    using vec1l = vec1<long>;
    using vec2l = vec2<long>;
    using vec3l = vec3<long>;
    using vec4l = vec4<long>;

    using vec1ul = vec1<unsigned long>;
    using vec2ul = vec2<unsigned long>;
    using vec3ul = vec3<unsigned long>;
    using vec4ul = vec4<unsigned long>;

    using vec1ll = vec1<long long>;
    using vec2ll = vec2<long long>;
    using vec3ll = vec3<long long>;
    using vec4ll = vec4<long long>;

    using vec1ull = vec1<unsigned long long>;
    using vec2ull = vec2<unsigned long long>;
    using vec3ull = vec3<unsigned long long>;
    using vec4ull = vec4<unsigned long long>;

    using vec1f32 = vec1<float>;
    using vec2f32 = vec2<float>;
    using vec3f32 = vec3<float>;
    using vec4f32 = vec4<float>;

    using vec1f64 = vec1<double>;
    using vec2f64 = vec2<double>;
    using vec3f64 = vec3<double>;
    using vec4f64 = vec4<double>;

    using vec1f128 = vec1<long double>;
    using vec2f128 = vec2<long double>;
    using vec3f128 = vec3<long double>;
    using vec4f128 = vec4<long double>;

} // namespace zephyr::math
