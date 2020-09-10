#pragma once

#include "Mesh.h"

//NonCopyable
class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();

	Model(Model&& other) noexcept;
	Model& operator= (Model&& other) noexcept;

	void AddData(const Mesh& mesh);
	void DeleteData();

	void GenVAO();
	void AddEBO(const std::vector<unsigned int>& indices);
	void AddVBO(int dimensions, const std::vector<float>& data);
	void BindVAO() const;

	int GetIndicesCount() const;
	
private:
	unsigned int m_VAO = 0;
	int m_VBOCount = 0; //still needed?
	int m_IndicesCount = 0;
	std::vector<unsigned int> m_Buffers; //maybe different name?
};

