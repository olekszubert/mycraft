#pragma once

#include <vector>

#include "Model.h"
#include "Shaders/Shader.h"
#include "Texture/BasicTexture.h"
//add texture atlas

//Why is this here...
class Camera;
class Entity;

class CubeRenderer
{
public:
	CubeRenderer();

	void Add(const Entity& entity);
	void Render(const Camera& camera);

private:
	std::vector<const Entity*> m_Cubes;

	Model m_CubeModel;
	//Shader m_Shader;
	BasicTexture m_BasicTexture;

	//TextureAtlas m_TextureAtlas;
};

