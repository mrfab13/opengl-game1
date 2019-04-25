#include "Input.h"
#include "Audio.h"
#include <iostream>
#include <freeglut.h>


using namespace std;

Audio audio;

enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_UP_FIRST,
	INPUT_DOWN_FIRST,
};

InputState KeyState[255];
InputState KeyStateS[255];


void Input::processInput() 
{

	if (KeyState['w'] == INPUT_DOWN || KeyStateS[GLUT_KEY_UP] == INPUT_DOWN)
	{
		objPos.y += 0.001f;

		audio.playSound(2);

	}
	if (KeyState['s'] == INPUT_DOWN || KeyStateS[GLUT_KEY_DOWN] == INPUT_DOWN)
	{
		objPos.y -= 0.001f;
	}
	if (KeyState['a'] == INPUT_DOWN || KeyStateS[GLUT_KEY_LEFT] == INPUT_DOWN)
	{
		objPos.x -= 0.001f;
	}
	if (KeyState['d'] == INPUT_DOWN || KeyStateS[GLUT_KEY_RIGHT] == INPUT_DOWN)
	{
		objPos.x += 0.001f;
	}
}


void Input::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

void Input::specialCharDown(unsigned int key, int x, int y)
{
	KeyStateS[key] = INPUT_DOWN;
}

void Input::specialCharUp(unsigned int key, int x, int y)
{
	KeyStateS[key] = INPUT_UP;
}