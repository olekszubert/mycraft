#include "Shader.h"

#include "ShaderLoader.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
    : m_id(loadShaders(vertexFile, fragmentFile))
{
    useProgram();
}


void Shader::loadInt(unsigned int location, int value)
{
    glUniform1i(location, value);
}

void Shader::loadFloat(unsigned int location, int value)
{
    glUniform1f(location, value);
}

void Shader::loadVector2(unsigned int location, const glm::vec2& vect)
{
    glUniform2f(location, vect.x, vect.y);
}

void Shader::loadVector3(unsigned int location, const glm::vec3& vect)
{
    glUniform3f(location, vect.x, vect.y, vect.z);
}

void Shader::loadVector4(unsigned int location, const glm::vec4& vect)
{
    glUniform4f(location, vect.x, vect.y, vect.z, vect.w);
}

void Shader::loadMatrix4(unsigned int location, const glm::mat4& matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::~Shader()
{
    glDeleteProgram(m_id);
}

void Shader::useProgram() const
{
    glUseProgram(m_id);
}

#if 0
//temporary hack
public:
    unsigned int ID;
    // activate the shader
    // ------------------------------------------------------------------------
    void use() const
    {
        glUseProgram(ID);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
#endif