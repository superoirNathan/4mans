#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Game.h"

#define WINDOW_SCREEN_WIDTH 640
#define WINDOW_SCREEN_HEIGHT 432

const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

Game* game;

void DisplayCallbackFunction(void)
{

	game->draw();

}

void KeyBoardCallbackFunction(unsigned char key, int x, int y)
{

	game->keyboardDown(key, x, y);

}

void KeyBoardUpCallbackFunction(unsigned char key, int x, int y)
{

	game->keyboardUp(key, x, y);

}

void TimerCallbackFunction(int value)
{

	game->update();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);

}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{

	game->mouseClicked(button, state, x, y);

}

void MouseMotionCallbackFunction(int x, int y)
{

	game->mouseMoved(x, y);

}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Tutrial1");

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{

		std::cout << "Glew could not be initialized," << std::endl;
		system("PAUSE");
		return 0;

	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	//setup callback functions
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyBoardCallbackFunction);
	glutKeyboardUpFunc(KeyBoardUpCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	//initialize game
	game = new Game();
	game->initializeGame();

	//start game
	glutMainLoop();

	return 0;

}