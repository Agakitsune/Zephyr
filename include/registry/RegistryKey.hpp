
#pragma once

#include <string>
#include <iostream>
#include <functional>

namespace zephyr::registry {
    
    class RegistryKey {
        std::string ns;
        std::string name;

        static std::string _default;

        static bool checkNamespace(char c);
        static bool checkName(char c);

        public:
            explicit RegistryKey(const std::string &name);
            explicit RegistryKey(const std::string &ns, const std::string &name);
            RegistryKey(const RegistryKey &other);
            RegistryKey(RegistryKey &&other);
            ~RegistryKey() = default;

            static void setDefaultNamespace(const std::string &ns);
            static const std::string &getDefaultNamespace();
            static RegistryKey of(const std::string &value);

            RegistryKey &operator=(const RegistryKey &other);
            RegistryKey &operator=(RegistryKey &&other);

            bool operator==(const RegistryKey &other) const;

            const std::string &getNamespace() const;
            const std::string &getName() const;

            std::string string() const;
    };

    std::ostream &operator<<(std::ostream &os, const RegistryKey &key);

}

template<>
struct std::hash<zephyr::registry::RegistryKey> {
    size_t operator()(const zephyr::registry::RegistryKey &key) const {
        return std::hash<std::string>()(key.string());
    }
};
