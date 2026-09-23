#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
  private:
    void check_shader_compilation(GLenum type);
    void check_shader_linking();

  public:
    unsigned int m_vertexID, m_fragmentID, m_ID;
    void init(const std::string& vertex_source, const std::string& fragment_source);
    void bind() { glUseProgram(m_ID); }
    void unbind() { glUseProgram(0); }

    void set_vec4f(const std::string &location, const glm::vec4 &vec);
    void set_mat4f(const std::string &location, const glm::mat4 *vec);
    void set_vec3f(const std::string &location, const glm::vec3 &vec);
    void set_1f(const std::string &location, const float &f);

    Shader();
};
