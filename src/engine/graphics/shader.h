#pragma once

#include <glad/gl.h>
#include <glm.hpp>
#include <string>
#include <unordered_map>

namespace lweng
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        bool create(const char* vertex_source, const char* fragment_source);
        void destroy();

        void bind() const;
        void unbind() const;

        void set_mat4(const std::string& name, const glm::mat4& val) const;
        void set_vec3(const std::string& name, const glm::vec3& val) const;
        void set_int(const std::string& name, const int val) const;
        void set_float(const std::string& name, const float val) const;

        GLuint get_program() const;
    private:
        GLint get_uniform_location(const std::string& name) const;

        GLuint m_program;
        mutable std::unordered_map<std::string, GLint> m_uniform_cache;
    };
}