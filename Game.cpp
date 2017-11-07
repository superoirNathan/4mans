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
    light1.position = glm::vec4(0.f, 4.f, 0.f, 1.f);
    light1.originalPosition = light1.position;
    light1.ambient = glm::vec3(0.05f);
    light1.diffuse = glm::vec3(0.7f);
    light1.specular = glm::vec3(1.f);
    light1.specularExponent = 50.f;
    light1.consantAttenuation = 1.f;
    light1.linearAttenuation = 0.1f;
    light1.quadraticAttenuation = 0.01f;

    light2.position = glm::vec4(0.f, -4.f, 0.f, 1.f);
    light2.originalPosition = light2.position;
    light2.ambient = glm::vec3(0.05f, 0.f, 0.f);
    light2.diffuse = glm::vec3(0.7f, 0.f, 0.f);
    light2.specular = glm::vec3(1.f, 0.f, 0.f);
    light2.specularExponent = 50.f;
    light2.consantAttenuation = 1.f;
    light2.linearAttenuation = 0.1f;
    light2.quadraticAttenuation = 0.01f;

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
    if (!phongColorSide.load("shaders/phongColorSide.vert", "shaders/phongColorSide.frag"))
    {

        std::cout << "Shaders failed to initialize" << std::endl;
        system("Pause");
        exit(0);

    }
	Mesh monkey; 
	if (!monkey.loadFromFile("meshes/Spaceship.obj"))
	{

		std::cout << "Model failed to load" << std::endl;
		system("pause");
		exit(0);

	
    }
    Mesh gorilla;
 //   if (!gorilla.loadFromFile("meshes/monkey.obj"))
    if (!gorilla.loadFromFile("meshes/road_proto.obj"))
    {

        std::cout << "Model failed to load" << std::endl;
        system("pause");
        exit(0);
    }




	monkey1 = GameObject(monkey);
    
    monkey1.loadTexture(TextureType::Diffuse, "textures/fur.png");
    monkey1.loadTexture(TextureType::Specular, "textures/monkeySpecular.png");

	monkey2 = GameObject(monkey); 

    monkey2.loadTexture(TextureType::Diffuse, "textures/fullSpecular.png");
    monkey2.loadTexture(TextureType::Specular, "textures/noSpecular.png");
    
    gorilla1 = GameObject(gorilla);
    gorilla1.loadTexture(TextureType::Diffuse, "textures/fullSpecular.png");
    gorilla1.loadTexture(TextureType::Specular, "textures/fullSpecular.png");

    cube = GameObject(monkey);


//	monkey1.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
//	monkey2.color = glm::vec4(0.f, 1.f, 0.f, 1.f);
//    gorilla1.color = glm::vec4(0.5f, 0.5f, 0.5f, 1.f);

	monkey2.translate = glm::translate(monkey2.transform, glm::vec3(2.f, 0.f, 0.f));
	monkey1.translate = glm::translate(monkey1.transform, glm::vec3(2.f, 2.f, 2.f));
    gorilla1.translate = glm::translate(gorilla1.transform, glm::vec3(0.f, 0.f, 10.f));
    cube.translate = glm::translate(cube.transform, glm::vec3(10.f, 10.f, 10.f));


	glm::vec3 temp = monkey1.translate * glm::vec4(0,0,0,1);

	cameraTransform = glm::lookAt(glm::vec3( temp - glm::vec3(0.f, 0.f, -5.f)  ), temp, glm::vec3(0.0, 1.0, 0.0));
	cameraProjection = glm::perspective(45.f, ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT), 0.1f, 10000.f);

}
//Happens once per frame, used to update state of the game
void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltatime = updateTimer->getElapsedTimeSeconds();

	if (shouldRotate)
	{

		monkey1.rotate = glm::rotate(monkey1.rotate, deltatime * (glm::pi <float>() / 4.f), glm::vec3(0.f, 1.f, 0.f));
		monkey2.rotate= glm::rotate(monkey2.rotate , deltatime * (glm::pi <float>() / 4.f), glm::vec3(0.f,1.f,0.f));
	}
    if (shouldLightSpin) 
    {
        lightSpinner = glm::rotate(lightSpinner, deltatime * (glm::pi <float>() / 2.f), glm::vec3(0.f, 0.f, 1.0));
        for (int i = 0; i < pointLights.size();i++) {

            pointLights[i].position = lightSpinner * pointLights[i].originalPosition ;
        }
    
    }

	if (wKeydown)
	{

		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0.f, deltatime*10));
		monkey2.translate = glm::translate(monkey2.translate, glm::vec3(0.f, 0.f, deltatime * 10));

	}
	if (sKeydown)
	{

		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, 0, -deltatime * 10));
		monkey2.translate = glm::translate(monkey2.translate, glm::vec3(0.f, 0, -deltatime * 10));

	}
	if (aKeydown)
	{

		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(deltatime *10, 0.f, 0.f));
		monkey2.translate = glm::translate(monkey2.translate, glm::vec3(deltatime *10, 0.f, 0.f));

	}
	if (dKeydown)
	{

		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(-deltatime *10, 0.f, 0.f));
		monkey2.translate = glm::translate(monkey2.translate, glm::vec3(-deltatime *10, 0.f , 0.f));

	}
	if (oKeydown)
	{

		monkey1.scale -= deltatime;
		monkey2.scale -= deltatime;

	}
	if (pKeydown)
	{

		monkey1.scale += deltatime;
		monkey2.scale += deltatime;

	}
    if (zKeydown)
    {
        camMove += glm::vec3(0.f, 0.f, 1.f);
    }
    if (xKeydown)
    {
        camMove -= glm::vec3(0.f, 0.f, 1.f);
    }
    if (cKeydown)
    {
        camMove += glm::vec3(0.f, 1.f, 0.f);
    }
    if (vKeydown)
    {
        camMove -= glm::vec3(0.f, 1.f, 0.f);
    }
    if (qKeydown)
    {
        camMove += glm::vec3(1, 0.f, 0.f);
    }
    if (eKeydown)
    {
        camMove -= glm::vec3(1, 0.f, 0.f);
    }

	//F = T * R * S
	monkey1.transform = monkey1.translate * monkey1.rotate * glm::scale(glm::mat4(), glm::vec3(monkey1.scale));
	monkey2.transform = monkey2.translate * monkey2.rotate * glm::scale(glm::mat4(), glm::vec3(monkey2.scale));
    gorilla1.transform = gorilla1.translate * gorilla1.rotate * glm::scale(glm::mat4(), glm::vec3(gorilla1.scale));

	glm::vec3 temp = monkey1.translate * glm::vec4(0,0,0,1);


        cameraTransform = glm::lookAt(glm::vec3(temp + camMove), temp, glm::vec3(0.0, 1.0, 0.0));
}

void Game::draw()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	monkey1.draw( phong, cameraTransform, cameraProjection, pointLights); 
	monkey2.draw( phong, cameraTransform, cameraProjection, pointLights);
	gorilla1.draw(phongNoTexture, cameraTransform, cameraProjection, pointLights);

    cube.draw(phongColorSide, cameraTransform, cameraProjection, pointLights);
	
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
		aKeydown = true;
		break;
	case 's':
		sKeydown = true;
	break;
	case 'd':
		dKeydown = true;
		break;
	case 'o':
		oKeydown = true;
		break;
	case 'p':
		pKeydown = true;
		break;
    case 'z':
        zKeydown = true;
        break;
    case 'x':
        xKeydown = true;
        break;
    case 'c':
        cKeydown = true;
        break;
    case 'v':
        vKeydown = true;
        break;
    case 'q':
        qKeydown = true;
        break;
    case 'e':
        eKeydown = true;
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
    case 'l':
        shouldLightSpin = !shouldLightSpin;
        break;
	case 'w':
		wKeydown = false;
		break;	   
	case 'a':	   
		aKeydown = false;
		break;	   
	case 's':	   
		sKeydown = false;
		break;	   
	case 'd':	   
		dKeydown = false;
		break;
	case 'o':
		oKeydown = false;
		break;
	case 'p':
		pKeydown = false;
		break;
    case 'z':
        zKeydown = false;
        break;
    case 'x':
        xKeydown = false;
        break;
    case 'c':
        cKeydown = false;
        break;
    case 'v':
        vKeydown = false;
        break;
    case 'q':
        qKeydown = false;
        break;
    case 'e':
        eKeydown = false;
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