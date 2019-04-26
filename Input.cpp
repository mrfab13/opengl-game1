#include <iostream>
#include <freeglut.h>
#include <vector>
#include "Input.h"
#include "Audio.h"
#include "ObjectManager.h"
#include "glm.hpp"



using namespace std;

Audio1 audio2;
ObjectManager objectmanager2;

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
	glm::vec3 temp;
	if (KeyState['w'] == INPUT_DOWN || KeyStateS[GLUT_KEY_UP] == INPUT_DOWN)
	{
		temp = objectmanager2.GetObjectPos();
		temp.y += 0.1f;
		objectmanager2.SetObjectPos(temp);
		audio2.playSound(2);
	}
	if (KeyState['s'] == INPUT_DOWN || KeyStateS[GLUT_KEY_DOWN] == INPUT_DOWN)
	{
		temp = objectmanager2.GetObjectPos();
		temp.y -= 0.001f;
		objectmanager2.SetObjectPos(temp);
	}
	if (KeyState['a'] == INPUT_DOWN || KeyStateS[GLUT_KEY_LEFT] == INPUT_DOWN)
	{
		temp = objectmanager2.GetObjectPos();
		temp.x -= 0.001f;
		objectmanager2.SetObjectPos(temp);
	}
	if (KeyState['d'] == INPUT_DOWN || KeyStateS[GLUT_KEY_RIGHT] == INPUT_DOWN)
	{
		temp = objectmanager2.GetObjectPos();
		temp.x += 0.001f;
		objectmanager2.SetObjectPos(temp);
	}
}


Input::Input()
{
}

Input::~Input()
{
}

void Input::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN;
}

void Input::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP;
}

void Input::specialCharDown(int key, int x, int y)
{
	KeyStateS[key] = INPUT_DOWN;
}

void Input::specialCharUp(int key, int x, int y)
{
	KeyStateS[key] = INPUT_UP;
}