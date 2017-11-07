#pragma once
#include <glm\glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"

#include <vector>

class GameObject
{
public:
	GameObject(); 
	GameObject(const Mesh &m); 
	~GameObject(); 
	Mesh mesh; 

	glm::mat4 transform; 
//	glm::vec4 color; 
//  Texture texture;
    Material mat;

	glm::mat4 translate; 
	glm::mat4 rotate; 
	float scale = 1; 

    void loadTexture(TextureType type, const std::string &texFile);


    glm::vec3 pos = translate * glm::vec4(1);

	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, 
		glm::mat4 &cameraProjection, std::vector<Light> &pointLights); 
};