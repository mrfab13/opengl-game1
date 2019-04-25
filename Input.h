#pragma once

class Input 
{

public:
	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void specialCharDown(unsigned int key, int x, int y);
	static void specialCharUp(unsigned int key, int x, int y);
	void processInput();

private:




};