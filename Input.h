#pragma once


class Input 
{

public:
	Input();
	~Input();
	static void KeyboardDown(unsigned char key, int x, int y);
	static void KeyboardUp(unsigned char key, int x, int y);
	static void specialCharDown(int key, int x, int y);
	static void specialCharUp(int key, int x, int y);
	void processInput();

private:




};