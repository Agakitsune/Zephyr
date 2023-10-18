
#pragma once

#include <string>

#include "Utils.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"

namespace zephyr::gl {

    class Program {
        GLuint handle;

        public:
            Program();
            Program(const Program&) = delete;
            Program(Program&&) noexcept;

            ~Program();

            Program& operator=(const Program&) = delete;
            Program& operator=(Program&&) noexcept;

            void attach(const Shader& shader) const;
            void detach(const Shader& shader) const;

            void link() const;

            std::string getInfoLog() const;

            void use() const;

            Uniform getUniform(const std::string& name) const;
    };

}
