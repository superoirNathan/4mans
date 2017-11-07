#include "Timer.h"
#include <GL/glut.h>

Timer::Timer()
{

	previousTime = glutGet(GLUT_ELAPSED_TIME);
	tick();

}

Timer::~Timer()
{

}

float Timer::tick()
{

	currentTime = glutGet(GLUT_ELAPSED_TIME);
	elapsedTime = currentTime - previousTime;
	previousTime = currentTime;

	return elapsedTime;

}
//Return delta time in Milliseconds
float Timer::getElapsedTimeMS()
{

	return elapsedTime;

}
//Return delta time in seconds
float Timer::getElapsedTimeSeconds()
{

	return elapsedTime / 1000.f;

}
//Get time since program start
float Timer::getCurrentTime()
{

	return currentTime;

}