#include "CubeRenderer.h"
#include <iostream>

#include "Paths.h"

CubeRenderer::CubeRenderer()
{
    //Hardcoded grass texture
    m_BasicTexture.LoadFromFile(grassTexPath);

    std::vector<float> vertexCoords
    {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,

        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,

        //Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,

        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,

        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,

        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1.
    };




    /*auto top = m_atlasTest.getTexture({ 0, 0 });
    auto side = m_atlasTest.getTexture({ 1, 0 });
    auto bottom = m_atlasTest.getTexture({ 2, 0 });*/

    //
    std::vector<float> texCoords;
    /*texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), side.begin(), side.end());
    texCoords.insert(texCoords.end(), top.begin(), top.end());
    texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());*/

    std::vector<unsigned int> indices
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //Create mesh and add to m_CubeModel
    m_CubeModel.AddData({ vertexCoords, texCoords, indices });
}