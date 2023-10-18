
#include "gl/Program.hpp"

namespace zephyr::gl {
    
    Program::Program() {
        handle = glCreateProgram();
    }

    Program::Program(Program&& other) noexcept {
        handle = other.handle;
        other.handle = 0;
    }

    Program::~Program() {
        glDeleteProgram(handle);
    }

    Program& Program::operator=(Program&& other) noexcept {
        handle = other.handle;
        other.handle = 0;
        return *this;
    }

    void Program::attach(const Shader& shader) const {
        glAttachShader(handle, shader.getHandle());
    }

    void Program::detach(const Shader& shader) const {
        glDetachShader(handle, shader.getHandle());
    }

    void Program::link() const {
        glLinkProgram(handle);
    }

    std::string Program::getInfoLog() const {
        GLint length;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length);
        char* log = new char[length];
        glGetProgramInfoLog(handle, length, nullptr, log);
        std::string result(log);
        delete[] log;
        return result;
    }

    void Program::use() const {
        glUseProgram(handle);
    }

    Uniform Program::getUniform(const std::string& name) const {
        return Uniform(glGetUniformLocation(handle, name.c_str()));
    }

} // namespace zephyr::gl
