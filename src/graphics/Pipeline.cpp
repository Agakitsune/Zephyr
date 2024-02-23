
#include "graphics/Pipeline.hpp"
#include "core/Core.hpp"

namespace zephyr::graphics {

    Pipeline::Pipeline(const std::string &json, const std::function<void(const gl::VertexArray &)> &setup) {
        std::ifstream file(json);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + json);
        
        nlohmann::json j;
        file >> j;
        file.close();

        std::string vertexName = j["vertex"];
        std::string fragmentName = j["fragment"];

        std::filesystem::path vertexPath = Core::resources() / "assets" / registry::RegistryKey::getDefaultNamespace() / "shader" / vertexName;
        std::filesystem::path fragmentPath = Core::resources() / "assets" / registry::RegistryKey::getDefaultNamespace() / "shader" / fragmentName;

        if (j.contains("geometry")) {
            std::string geometryName = j["geometry"];
            std::filesystem::path geometryPath = Core::resources() / "assets" / registry::RegistryKey::getDefaultNamespace() / "shader" / geometryName;
            _program = utils::loadProgram(vertexPath, geometryPath, fragmentPath);
        } else {
            _program = utils::loadProgram(vertexPath, fragmentPath);
        }

        setup(_array);
    }

    Pipeline::Pipeline(const std::filesystem::path &file, const std::function<void(const gl::VertexArray &)> &setup) : Pipeline(file.string(), setup) {}

    Pipeline::Pipeline(const std::string &vertexPath, const std::string &fragmentPath, const std::function<void(const gl::VertexArray &)> &setup) {
        _program = utils::loadProgram(vertexPath, fragmentPath);
        setup(_array);
    }

    Pipeline::Pipeline(const std::string &vertexPath, const std::string &geometryPath, const std::string &fragmentPath, const std::function<void(const gl::VertexArray &)> &setup) {
        _program = utils::loadProgram(vertexPath, geometryPath, fragmentPath);
        setup(_array);
    }

    Pipeline::Pipeline(const gl::Program &program) : _program(program) {}

    Pipeline::Pipeline(gl::Program &&program) : _program(std::move(program)) {}

    void Pipeline::use() const {
        _array.bind();
        _program.use();
    }

    void Pipeline::unuse() const {}

    void Pipeline::set(const std::string &uniform, GLfloat v0) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0);
    }

    void Pipeline::set(const std::string &uniform, GLfloat v0, GLfloat v1) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1);
    }

    void Pipeline::set(const std::string &uniform, GLfloat v0, GLfloat v1, GLfloat v2) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2);
    }

    void Pipeline::set(const std::string &uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2, v3);
    }

    void Pipeline::set(const std::string &uniform, GLint v0) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0);
    }

    void Pipeline::set(const std::string &uniform, GLint v0, GLint v1) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1);
    }

    void Pipeline::set(const std::string &uniform, GLint v0, GLint v1, GLint v2) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2);
    }

    void Pipeline::set(const std::string &uniform, GLint v0, GLint v1, GLint v2, GLint v3) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2, v3);
    }

    void Pipeline::set(const std::string &uniform, GLuint v0) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0);
    }

    void Pipeline::set(const std::string &uniform, GLuint v0, GLuint v1) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1);
    }

    void Pipeline::set(const std::string &uniform, GLuint v0, GLuint v1, GLuint v2) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2);
    }

    void Pipeline::set(const std::string &uniform, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(v0, v1, v2, v3);
    }

    void Pipeline::set(const std::string &uniform, GLsizei count, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(count, value);
    }

    void Pipeline::set(const std::string &uniform, GLsizei count, const GLint *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(count, value);
    }

    void Pipeline::set(const std::string &uniform, GLsizei count, const GLuint *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set(count, value);
    }

    void Pipeline::set2x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set2x2(count, transpose, value);
    }

    void Pipeline::set3x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set3x3(count, transpose, value);
    }

    void Pipeline::set4x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set4x4(count, transpose, value);
    }

    void Pipeline::set2x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set2x3(count, transpose, value);
    }

    void Pipeline::set3x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set3x2(count, transpose, value);
    }

    void Pipeline::set2x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set2x4(count, transpose, value);
    }

    void Pipeline::set4x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set4x2(count, transpose, value);
    }

    void Pipeline::set3x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set3x4(count, transpose, value);
    }

    void Pipeline::set4x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const {
        gl::Uniform u = _program.getUniform(uniform);
        if (!u.isValid())
            return;
        u.set4x3(count, transpose, value);
    }

}
