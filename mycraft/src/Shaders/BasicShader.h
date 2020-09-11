#pragma once
#include "Shader.h"

class BasicShader : public Shader
{
public:
    BasicShader(const std::string& vertexFile = "BasicVertex",
        const std::string& fragmentFile = "BasicFragment");

    void loadProjectionViewMatrix(const glm::mat4& pvMatrix);
    void loadModelMatrix(const glm::mat4& matrix);

private:
    virtual void getUniforms() override;

    unsigned int m_locationProjectionViewMatrix;
    unsigned int m_locationModelMatrix;
};