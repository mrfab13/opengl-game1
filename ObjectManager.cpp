#include "ObjectManager.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

glm::vec3 ObjectManager::GetObjectPos()
{
	return (objPos);
}

glm::vec3 ObjectManager::SetObjectPos(glm::vec3 temp)
{
	objPos = temp;

	return (objPos);
}


