#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "glm.hpp"


class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager();
	glm::vec3 GetObjectPos();
	glm::vec3 SetObjectPos(glm::vec3);

private:
	glm::vec3 objPos = glm::vec3(0.0f, 0.0f, 0.0f);
};