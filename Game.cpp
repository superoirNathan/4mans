#include "Game.h"
#include <iostream>
#include <GL/glut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Game::Game()
{

}

Game::~Game()
{

	delete updateTimer;

	phongNoTexture.unload();
	

}
//Happens at the beggining of game
void Game::initializeGame()
{

	updateTimer = new Timer();

	glEnable(GL_DEPTH_TEST);
	
    Light light1, light2;
    light1.position = glm::vec4(0.f, 10.f, 0.f, 1.f);
    light1.originalPosition = light1.position;
    light1.ambient = glm::vec3(0.0f);
    light1.diffuse = glm::vec3(1.5f);
    light1.specular = glm::vec3(1.f);
    light1.specularExponent = 50.f;
    light1.consantAttenuation = 1.f;
    light1.linearAttenuation = 0.1f;
    light1.quadraticAttenuation = 0.01f;

	pointLights.push_back(light1);
	pointLights.push_back(light2);

	if (!phongNoTexture.load("shaders/Phong.vert", "shaders/PhongNoTexture.frag"))
	{

		std::cout << "Shaders failed to initialize" << std::endl;
		system("Pause");
		exit(0);

	}
    if (!phong.load("shaders/Phong.vert", "shaders/Phong.frag"))
    {

        std::cout << "Shaders failed to initialize" << std::endl;
        system("Pause");
        exit(0);

    }
	Mesh player; 
	if (!player.loadFromFile("meshes/Spaceship.obj"))
	{

		std::cout << "Model failed to load" << std::endl;
		system("pause");
		exit(0);
    }
    Mesh road_S;
    if (!road_S.loadFromFile("meshes/road_Straight.obj"))
    {
        std::cout << "Model failed to load" << std::endl;
        system("pause");
        exit(0);
    }

 
    
	vehicle.mesh = (player);
    temple.mesh = (road_S);
    start.mesh = (road_S);
    end.mesh = (road_S);

    

    vehicle.loadTexture(TextureType::Diffuse, "textures/Spaceship_Model.png");
    vehicle.loadTexture(TextureType::Specular, "textures/FullSpecular.png");
    vehicle.translate = glm::translate(vehicle.transform, glm::vec3(0.f, 2.f, 2.f));
    
    temple.loadTexture(TextureType::Diffuse, "textures/road.png");
    temple.loadTexture(TextureType::Specular, "textures/FullSpecular.png");   
    temple.translate = glm::translate(vehicle.transform, glm::vec3(0.f, -2.f, -10.f));
    
    start.loadTexture(TextureType::Diffuse, "textures/road.png");
    start.loadTexture(TextureType::Specular, "textures/FullSpecular.png");
    start.translate = glm::translate(vehicle.transform, glm::vec3(0.f, -2.f, 0.f));

    for (int i = 0; i < 30; i++) {
        middle.push_back(new Road(end));
        middle[i]->loadTexture(TextureType::Diffuse, "textures/road.png");
        middle[i]->loadTexture(TextureType::Specular, "textures/FullSpecular.png");

        middle[i]->translate = glm::translate(vehicle.transform, glm::vec3(0.f, -2.f, (-10 * i) - 20));
    }


    end = start;
    end.translate = glm::translate(vehicle.transform, glm::vec3(0.f, -2.f, -20.f));



	glm::vec3 temp = vehicle.translate * glm::vec4(0,0,0,1);
	vehicle.forwardDir = glm::vec4(0, 0, 1, 1);
	vehicle.originalDir = glm::vec4(0, 0, 1, 1);

    temple.transform = temple.translate * vehicle.rotate * glm::scale(glm::mat4(), glm::vec3(vehicle.scale));
    start.transform = start.translate * vehicle.rotate * glm::scale(glm::mat4(), glm::vec3(vehicle.scale));
    end.transform = end.translate * vehicle.rotate * glm::scale(glm::mat4(), glm::vec3(vehicle.scale));
    for (int i = 0; i < 30; i++) {
        middle.push_back(new Road(end));
        middle[i]->transform = middle[i]->translate * vehicle.rotate * glm::scale(glm::mat4(), glm::vec3(vehicle.scale));
    }

	cameraTransform = glm::lookAt(temp + glm::vec3(0, 2, -5), temp + glm::vec3(0,0,5), glm::vec3(0.0, 1.0, 0.0));
	cameraProjection = glm::perspective(45.f, ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), 0.1f, 10000.f);



    {
    
        //please forgive my tardiness, I was half asleep

        emitter.playing = true;
        emitter.interpolateColour = false;

        //Physics properties
        emitter.velocity0 = glm::vec3(0.0f, 0.0f, 0.0f);
        emitter.velocity1 = glm::vec3(0.0f, 0.0f, 0.0f);
        emitter.emitterPosition = glm::vec3(0.f, 0.f, 0.f);
        emitter.boxWH = glm::vec3(50.0f);
        emitter.boxOn = false;
        //Steer properties                         
        emitter.taretgOn = false;
        emitter.fleeOn = false;
        emitter.magnetOn = false;
        emitter.repelOn = false;
        emitter.gravityOn = false;
        emitter.pathOn = false;

        emitter.targetPos = glm::vec3(0.0f);
        emitter.fleePos = glm::vec3(0.0f);
        emitter.magnetPos = glm::vec3(0.0f);
        emitter.repelPos = glm::vec3(0.0f);
        emitter.gravity = glm::vec3(0.0f, 1.0f, 0.0f);
        emitter.pathEnd = glm::vec3(0.0f);

        emitter.targetStrength = 0.0f;
        emitter.fleeStrength = 0.0f;
        emitter.magnetStrength = 0.0f;
        emitter.magnetRadius = 0.0f;
        emitter.repelStrength = 0.0f;
        emitter.repelRadius = 0.0f;

        // Range Properties
        emitter.colour0 = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        emitter.colour1 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        emitter.lifeRange = glm::vec2(1.0f, 2.0f);
        emitter.sizeRange = glm::vec2(15.0f, 25.0f);
        emitter.spawnRange = glm::vec2(1.0f, 5.0f);
        emitter.massRange = glm::vec2(0.5f, 0.75f);

        emitter.emitterName = "emitter";

        //other
        emitter.durationOn = true;
        emitter.durationRepeat = false;
        emitter.durationOnX_OffY = glm::vec2(0.0f, 0.0f);
        emitter.catmullT0 = glm::vec3(0);
        emitter.catmullT1 = glm::vec3(0);
        emitter.pathPointStrength = 0.0f;
        emitter.step = 7;
        emitter.showEmitter = true;
        emitter.circleSquare = true;
    }
}
//Happens once per frame, used to update state of the game
void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltatime = updateTimer->getElapsedTimeSeconds();
    vehicle.update2(deltatime);
    emitter.update(deltatime);
	if (shouldRotate)
	{

		vehicle.rotate = glm::rotate(vehicle.rotate, deltatime * (glm::pi <float>() / 4.f), glm::vec3(0.f, 1.f, 0.f));

		vehicle.forwardDir = vehicle.rotate * vehicle.originalDir;
        vehicle.force += (glm::vec3(vehicle.forwardDir));

	}
	if (shouldRotateRight)
	{

		vehicle.rotate = glm::rotate(vehicle.rotate, -deltatime * (glm::pi <float>() / 4.f), glm::vec3(0.f, 1.f, 0.f));

		vehicle.forwardDir = vehicle.rotate * vehicle.originalDir;
        vehicle.force += (glm::vec3(vehicle.forwardDir));

	}

    if (wKeydown)
    {

        //		vehicle.translate = glm::translate(vehicle.translate, glm::vec3(vehicle.forwardDir*deltatime * 5.0f));
        vehicle.force += (glm::vec3(vehicle.forwardDir) * 3.0f);
    }
    else
        vehicle.force = glm::vec3(0.0f);

	if (sKeydown)
	{
		vehicle.translate = glm::translate(vehicle.translate, glm::vec3(vehicle.forwardDir*-deltatime));
	}
    vehicle.translate = glm::translate(vehicle.translate, glm::vec3( vehicle.velocity));

    //F = T * R * S

	vehicle.transform = vehicle.translate * vehicle.rotate * glm::scale(glm::mat4(), glm::vec3(vehicle.scale));


	glm::vec3 carPosition = vehicle.transform * glm::vec4(0,0,0,1);

	glm::mat4 pivot = vehicle.transform * glm::rotate(glm::mat4(), 3.14f, glm::vec3(0.f, 1.f, 0.f));

	cameraTransform = pivot * (glm::translate(glm::mat4(), glm::vec3(0.f, 4.f, 6.f)) * glm::rotate(glm::mat4(), -0.19739674f, glm::vec3(1.f, 0.f, 0.f)));
	cameraTransform = glm::inverse(cameraTransform);
	glm::vec4 camPos = cameraTransform * glm::vec4(0, 0, 0, 1);
    
}

void Game::draw()
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vehicle.draw(phong, cameraTransform, cameraProjection, pointLights); 
    temple.draw(phong, cameraTransform, cameraProjection, pointLights);
     start.draw(phong, cameraTransform, cameraProjection, pointLights);
     end.draw(phong, cameraTransform, cameraProjection, pointLights);

     for (int i = 0; i < 30; i++) {
         middle[i]->draw(phong, cameraTransform, cameraProjection, pointLights);
     }
     
     glutSwapBuffers();

}

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{

	switch (key)
	{
	case 27: //esc key
	case '27':
		exit(1);
		break;
	case 't':
		std::cout << "Total elapsed time: " << updateTimer->getCurrentTime();
		break;
	case 'w':
		wKeydown = true;
		break;
	case 'a':
		shouldRotate = true;
		break;
	case 's':
		sKeydown = true;
	break;
	case 'd':
		shouldRotateRight = true;
		break;
    default:
		break;
	}

}

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{

	switch (key)
	{
	case 'r':
		shouldRotate = !shouldRotate;
		break;
	case 'w':
		wKeydown = false;
		break;	   
	case 'a':	   
		shouldRotate = false;
		break;	   
	case 's':	   
		sKeydown = false;
		break;	   
	case 'd':	   
		shouldRotateRight = false;
		break;

	default:
		break;
	}

}

void Game::mouseClicked(int button, int state, int x, int y)
{

	if (state = GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
        case 'p':
            vehicle.forwardDir = glm::vec4(0, 0, 1, 1);
            vehicle.originalDir = glm::vec4(0, 0, 1, 1);
            break;
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
		}
	}

}

void Game::mouseMoved(int x, int y)
{



}