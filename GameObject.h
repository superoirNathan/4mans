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
    glm::vec4 originalDir;


    glm::vec3 pos = translate * glm::vec4(1);

	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, 
		glm::mat4 &cameraProjection, std::vector<Light> &pointLights); 

    // Physics properties
    // Position is where the particle currently is
    // Velocity is the rate of change of position
    // Acceleration is the rate of change of velocity
    // p' = p + v*dt + 0.5*a*dt^2
    // current position is the previous position plus the change in position multiplied by the amount of time passed since we last calculated position
    // v' = v + a*dt
    glm::vec4 forwardDir;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    glm::vec3 force;
    float mass;

    void update2(float dt);

};

