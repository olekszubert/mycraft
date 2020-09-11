#pragma once

#if 0
#include <vector>
#include "BasicTexture.h"

class TextureAtlas : public BasicTexture
{
public:
	TextureAtlas(const std::string& path);

	std::vector<float> GetTexture(const);
private:
	int m_ImageSize;
	int m_IndividualTextureSize;
};

#endif