#pragma once

#include <vector>

struct Mesh
{
	std::vector<float> vertexPositions;
	std::vector<float> textureCoords;
	std::vector<unsigned int> indices;
};