
#pragma once

#include <unordered_map>
#include <functional>
#include <fstream>
#include <filesystem>

#include "gl/Program.hpp"
#include "gl/VertexArray.hpp"

#include "utils/Program.hpp"

#include "json.hpp"

namespace zephyr::graphics {

    class Pipeline {
        protected:
            gl::VertexArray _array;
            gl::Program _program;

        public:
            Pipeline(const std::string &file, const std::function<void(const gl::VertexArray &)> &setup);
            Pipeline(const std::filesystem::path &file, const std::function<void(const gl::VertexArray &)> &setup);
            Pipeline(const std::string &vertexPath, const std::string &fragmentPath, const std::function<void(const gl::VertexArray &)> &setup);
            Pipeline(const std::string &vertexPath, const std::string &geometryPath, const std::string &fragmentPath, const std::function<void(const gl::VertexArray &)> &setup);
            Pipeline(const gl::Program &program);
            Pipeline(gl::Program &&program);
            Pipeline(const Pipeline &other) = default;
            Pipeline(Pipeline &&other) noexcept = default;

            virtual ~Pipeline() = default;

            virtual void use() const;
            virtual void unuse() const;

            void set(const std::string &uniform, GLfloat v0) const;
            void set(const std::string &uniform, GLfloat v0, GLfloat v1) const;
            void set(const std::string &uniform, GLfloat v0, GLfloat v1, GLfloat v2) const;
            void set(const std::string &uniform, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
            
            void set(const std::string &uniform, GLint v0) const;
            void set(const std::string &uniform, GLint v0, GLint v1) const;
            void set(const std::string &uniform, GLint v0, GLint v1, GLint v2) const;
            void set(const std::string &uniform, GLint v0, GLint v1, GLint v2, GLint v3) const;
            
            void set(const std::string &uniform, GLuint v0) const;
            void set(const std::string &uniform, GLuint v0, GLuint v1) const;
            void set(const std::string &uniform, GLuint v0, GLuint v1, GLuint v2) const;
            void set(const std::string &uniform, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
            
            void set(const std::string &uniform, GLsizei count, const GLfloat *value) const;
            void set(const std::string &uniform, GLsizei count, const GLint *value) const;
            void set(const std::string &uniform, GLsizei count, const GLuint *value) const;
            
            template<size_t N, typename T>
            requires std::is_integral_v<T> && std::is_signed_v<T>
            void set(const std::string &uniform, const math::vector<N, T> &vector) const {
                if constexpr (N == 1) {
                    set(uniform, vector.x);
                } else if constexpr (N == 2) {
                    set(uniform, vector.x, vector.y);
                } else if constexpr (N == 3) {
                    set(uniform, vector.x, vector.y, vector.z);
                } else if constexpr (N == 4) {
                    set(uniform, vector.x, vector.y, vector.z, vector.w);
                }
            }

            template<size_t N, typename T>
            requires std::is_integral_v<T> && std::negation_v<std::is_signed<T>>
            void set(const std::string &uniform, const math::vector<N, T> &vector) const {
                if constexpr (N == 1) {
                    set(uniform, vector.x);
                } else if constexpr (N == 2) {
                    set(uniform, vector.x, vector.y);
                } else if constexpr (N == 3) {
                    set(uniform, vector.x, vector.y, vector.z);
                } else if constexpr (N == 4) {
                    set(uniform, vector.x, vector.y, vector.z, vector.w);
                }
            }

            template<size_t N, typename T>
            requires std::is_floating_point_v<T>
            void set(const std::string &uniform, const math::vector<N, T> &vector) const {
                if constexpr (N == 1) {
                    set(uniform, vector.x);
                } else if constexpr (N == 2) {
                    set(uniform, vector.x, vector.y);
                } else if constexpr (N == 3) {
                    set(uniform, vector.x, vector.y, vector.z);
                } else if constexpr (N == 4) {
                    set(uniform, vector.x, vector.y, vector.z, vector.w);
                }
            }

            void set2x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
            void set3x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
            void set4x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;

            void set2x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
            void set3x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;

            void set2x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
            void set4x2(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;

            void set3x4(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
            void set4x3(const std::string &uniform, GLsizei count, GLboolean transpose, const GLfloat *value) const;
    };

}
