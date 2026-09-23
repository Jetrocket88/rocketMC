#include "renderer/shader.hpp"

Shader::Shader() { }


void Shader::init(const std::string& vertex_source, const std::string& fragment_source) {

    this->m_vertexID   = glCreateShader(GL_VERTEX_SHADER  );
    this->m_fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vShaderCode = vertex_source.c_str();
    const char* fShaderCode = fragment_source.c_str();

    glShaderSource(this->m_vertexID, 1, &vShaderCode, NULL);
    glCompileShader(this->m_vertexID);
    check_shader_compilation(GL_VERTEX_SHADER);
    std::cout << "vertex_source: \n" << vertex_source << '\n';

    glShaderSource(this->m_fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(this->m_fragmentID);
    check_shader_compilation(GL_FRAGMENT_SHADER);
    std::cout << "fragment_source: \n" << fragment_source << '\n';

    std::cout << "Shader compiled successfully!\n";

    m_ID = glCreateProgram();

    glAttachShader(m_ID, this->m_vertexID  );
    glAttachShader(m_ID, this->m_fragmentID);

    glLinkProgram(m_ID);
    glUseProgram(m_ID);

    glDeleteShader(this->m_vertexID  );
    glDeleteShader(this->m_fragmentID);
}


void Shader::check_shader_compilation(GLenum type) {
    unsigned int shader {};
    if (type == GL_VERTEX_SHADER) { shader = this->m_vertexID; }
    else if (type == GL_FRAGMENT_SHADER) { shader = this->m_fragmentID; } 

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return;
}

void Shader::check_shader_linking() {
    int  success;
    char infoLog[512];
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        std::cout << "ERROR:SHADER:PROGRAM:LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::set_vec4f(const std::string& location, const glm::vec4& vec) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniform4f(address, vec.x, vec.y, vec.z, vec.w);
    return; 
}


void Shader::set_mat4f(const std::string& location, const glm::mat4* mat) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniformMatrix4fv(address, 1, GL_FALSE, glm::value_ptr(*mat));
}

void Shader::set_vec3f(const std::string& location, const glm::vec3& vec) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniform3f(address, vec.x, vec.y, vec.z);
}

void Shader::set_1f(const std::string& location, const float& f) {
    int address = glGetUniformLocation(m_ID, location.c_str());
    this->bind();
    glUniform1f(address, f);
}
