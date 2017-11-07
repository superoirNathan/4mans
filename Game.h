#pragma once

#include "Mesh.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Light.h"

#include <vector>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMES_PER_SECOND 60

class Game
{

public:
	Game();
	~Game();

	void initializeGame();
	void update();
	void draw();

	//Input callback functions
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);

	//Data Member
	Timer* updateTimer = nullptr;
	GameObject monkey1, monkey2, gorilla1, cube; 
	ShaderProgram passThrough;
	ShaderProgram phongNoTexture;
    ShaderProgram phongColorSide;
    ShaderProgram phong;
    std::vector<Light> pointLights;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
    glm::mat4 lightSpinner;


private:
	bool shouldRotate;
    bool shouldLightSpin = false;
	bool wKeydown;
	bool aKeydown;
	bool sKeydown;
	bool dKeydown;
	bool oKeydown;
	bool pKeydown;

    bool zKeydown;
    bool xKeydown;
    bool cKeydown;
    bool vKeydown;
    bool qKeydown;
    bool eKeydown;

    glm::vec3 camMove = glm::uvec3(0.f, 1.f, 0.f);


};