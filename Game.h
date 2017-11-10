#pragma once

#include "Mesh.h"
#include "Road.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Light.h"
#include "ParticleEmitter.h"
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
	GameObject vehicle; 
    GameObject temple;
    Road start;
    Road end;
    std::vector<Road*> middle;
    ParticleEmitter emitter;

	ShaderProgram passThrough;
	ShaderProgram phongNoTexture;
    ShaderProgram phongColorSide;
    ShaderProgram phong;
    std::vector<Light> pointLights;
    

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;

private:
	bool shouldRotate;
	bool shouldRotateRight;
	bool wKeydown;
	bool sKeydown;

};