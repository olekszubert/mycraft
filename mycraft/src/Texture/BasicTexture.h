#pragma once

#include <string>
#include <glad/glad.h>

class BasicTexture
{
public:
	BasicTexture() = default;
	BasicTexture(const std::string& path);
	~BasicTexture();

	void LoadFromFile(const std::string& path);
	void BindTexture() const;

private:
	unsigned int m_id;
};

