#include "BasicTexture.h"

#include <glad/glad.h>
#include <Stb/stb_image.h>
#include <iostream>
#include "Paths.h"

BasicTexture::BasicTexture(const std::string& path)
{
    LoadFromFile(path);
}

void BasicTexture::LoadFromFile(const std::string& path)
{
    //Create a texture - the number of texture names to be generated, array in which the generated texture names are stored
    glGenTextures(1, &m_id);
    //Bind the texture to perform operations on it
    BindTexture();

    //Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Load image, create texture and generate mipmaps
    int width, height, nrChannels;

    //Tell stb_image.h to flip loaded texture's on the y-axis
    stbi_set_flip_vertically_on_load(true); 

    //unsigned char* data = stbi_load(grassTexPath, &width, &height, &nrChannels, 0);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //jpg
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void BasicTexture::BindTexture() const
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

BasicTexture::~BasicTexture()
{
    glDeleteTextures(1, &m_id);
}
