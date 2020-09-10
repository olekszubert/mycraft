#include "Model.h"
#include "glad/glad.h"

Model::Model(const Mesh& mesh)
{
	AddData(mesh);
}

Model::~Model()
{
    DeleteData();
}

Model::Model(Model&& other) noexcept
    : m_VAO(other.m_VAO), m_VBOCount(other.m_VBOCount), m_IndicesCount(other.m_IndicesCount), m_Buffers(std::move(other.m_Buffers))
{
    other.m_VAO = 0;
    other.m_VBOCount = 0;
    other.m_IndicesCount = 0;
}

Model& Model::operator=(Model&& other) noexcept
{
    m_VAO = other.m_VAO; m_VBOCount = other.m_VBOCount; m_IndicesCount = other.m_IndicesCount; m_Buffers = std::move(other.m_Buffers);

    other.m_VAO = 0;
    other.m_VBOCount = 0;
    other.m_IndicesCount = 0;

    return *this;
}


void Model::AddData(const Mesh& mesh)
{
    GenVAO();

    AddVBO(3, mesh.vertexPositions);
    AddVBO(2, mesh.textureCoords);
    AddEBO(mesh.indices);
}

void Model::GenVAO()
{
    //
    if (m_VAO != 0)
        DeleteData();

    //
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

void Model::BindVAO() const
{
    glBindVertexArray(m_VAO);
}

void Model::AddVBO(int dimensions, const std::vector<float>& data)
{
    unsigned int VBO;

    //Generate VBO, Bind it, Push data into it from 'data'
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    //Position attribute
    glVertexAttribPointer(m_VBOCount, dimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(m_VBOCount++);

    //Add to private member vector buffer
    m_Buffers.push_back(VBO);
}

void Model::AddEBO(const std::vector<unsigned int>& indices)
{
    unsigned int EBO;

    //
    m_IndicesCount = indices.size();
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Model::DeleteData()
{
    //
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(m_Buffers.size(), m_Buffers.data());
    m_Buffers.clear();

    m_VBOCount = 0;
    m_VAO = 0;
    m_IndicesCount = 0;
}

int Model::GetIndicesCount() const
{
    return m_IndicesCount;
}
