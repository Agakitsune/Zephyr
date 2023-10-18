
#include "utils/Shader.hpp"

#include <fstream>

namespace zephyr::utils {
    
    gl::Shader loadShader(const std::string &path, gl::ShaderType type) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + path);
        }
        std::string source;
        std::string line;
        while (std::getline(file, line)) {
            source += line + '\n';
        }
        gl::Shader shader(type);
        shader.source(source);
        if (!shader.compile())
            throw std::runtime_error("Could not compile shader: " + shader.getInfoLog());
        return shader;
    }

} // namespace zephyr::utils
