#pragma once
#include <glm\\glm.hpp>

class Light
{
public:
    Light();
    ~Light();


    glm::vec4 originalPosition;
    glm::vec4 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float specularExponent;
    float consantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

private:

};

