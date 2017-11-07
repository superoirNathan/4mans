#pragma once
#include<glm\glm.hpp>
#include "Texture.h"

class Material
{
public:
    Material();
    Material(std::string diffusePath, std::string specularPath, float specExp = 0.f, glm::vec3 &hue = glm::vec3(1.0f, 1.0f, 1.0f));

    ~Material();

    void loadTexture(TextureType type, std::string texFile);

    //Data members

    Texture diffuse, specular;
    glm::vec3 hue = glm::vec3(1.0f, 1.0f, 1.0f);
    float specularExponent = 50.f;

};