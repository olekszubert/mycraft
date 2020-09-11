#pragma once
#include <string>
#include <glad/glad.h>

#include "../Maths/glm.h"

//#include "../Util/NonCopyable.h"

class Shader// : NonCopyable
{
public:
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    ~Shader();

    void useProgram() const;

    void loadInt(unsigned int location, int value);
    void loadFloat(unsigned int location, int value);

    void loadVector2(unsigned int location, const glm::vec2& vect);
    void loadVector3(unsigned int location, const glm::vec3& vect);
    void loadVector4(unsigned int location, const glm::vec4& vect);

    void loadMatrix4(unsigned int location, const glm::mat4& matrix);

protected:
    virtual void getUniforms() = 0;
    unsigned int m_id;
};