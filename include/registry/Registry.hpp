
#pragma once

#include <unordered_map>
#include <memory>

#include "registry/RegistryKey.hpp"

namespace zephyr::registry {

    template<typename T>
    class Registry;

    class UnknownRegistry {
        protected:
            bool _freeze = false;

        public:
            UnknownRegistry() = default;
            virtual ~UnknownRegistry() = default;

            void freeze() {
                _freeze = true;
            }

            template<typename T>
            Registry<T> &as() {
                return dynamic_cast<Registry<T>&>(*this);
            }
    };

    template<typename T>
    class Registry : public UnknownRegistry {
        std::unordered_map<RegistryKey, std::unique_ptr<T>> _values;

        public:
            Registry() = default;
            Registry(const Registry &other) = delete;
            Registry(Registry &&other) noexcept = default;
            virtual ~Registry() override = default;

            T &get(const std::string &key) {
                return get(RegistryKey::of(key));
            }

            const T &get(const std::string &key) const {
                return get(RegistryKey::of(key));
            }

            T &get(const RegistryKey &key) {
                return *_values.at(key);
            }

            const T &get(const RegistryKey &key) const {
                return *_values.at(key);
            }

            template<typename U>
            T &registerValue(const RegistryKey &key, const U &value) {
                if (_freeze) {
                    throw std::runtime_error("Registry is frozen");
                }
                _values[key] = std::make_unique<U>(value);
                return *_values[key];
            }

            template<typename U>
            T &registerValue(const RegistryKey &key, U &&value) {
                if (_freeze) {
                    throw std::runtime_error("Registry is frozen");
                }
                _values[key] = std::make_unique<U>(std::move(value));
                return *_values[key];
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::iterator begin() {
                return _values.begin();
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::iterator end() {
                return _values.end();
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::const_iterator begin() const {
                return _values.begin();
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::const_iterator end() const {
                return _values.end();
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::const_iterator cbegin() const {
                return _values.cbegin();
            }

            typename std::unordered_map<RegistryKey, std::unique_ptr<T>>::const_iterator cend() const {
                return _values.cend();
            }
    };

}
