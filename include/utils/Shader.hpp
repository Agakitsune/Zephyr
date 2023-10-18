
#pragma once

#include "gl/Shader.hpp"

namespace zephyr::utils {
    
    gl::Shader loadShader(const std::string& path, gl::ShaderType type);

} // namespace zephyr::utils
