#include <algorithm>
#include <iostream>
#include <ctime>

#include "ElementsModule.h"
#include "Configuration.h"

int ElementsModule::init()
{
	_objectsInfoByZone = {
		{
			{34, RESOURCES_PATH "/models/Rock1.obj", "", ""},
			{90, RESOURCES_PATH "/models/Tree1.obj", "", ""},
			{33, RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg", RESOURCES_PATH "/sound/drumloop.wav"}
		}, //zone 0 : mountain
		{
			{33, RESOURCES_PATH "/models/Rock2.obj", "", ""},
			{90, RESOURCES_PATH "/models/Tree2.obj", "", ""}
		}, //zone 1 : forest
		{
			{33, RESOURCES_PATH "/models/Rock3.obj", "", ""},
			{33, RESOURCES_PATH "/models/Tree3.obj", "", RESOURCES_PATH "/sound/cicadas.mp3"},
			{34, RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg", ""}
		} //zone 2 : beach
		};
	srand(time(0));
	putElementsOfZone(1);
	return 0;
}

void ElementsModule::putElementsOfZone(int zone)
{
	if (_elements.size() > 0)
		clear();
	for (auto const &objInfo : _objectsInfoByZone[zone])
	{
		createObjectsFromName(100, 10000, 10000, objInfo); //nbTotalElements, width, height
	}
}

void ElementsModule::clear()
{
	for (std::shared_ptr<Object> obj : _elements)
	{
		obj->remove();
	}
	_elements.clear();
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

void ElementsModule::SetVolume(float vol)
{
	for (std::shared_ptr<Object> elem : _elements)
	{
		elem->SetVolume(vol);
	}
}

glm::vec3 ElementsModule::getXYPos(int width, int height)
{
	glm::vec3 value = glm::linearRand(
			glm::vec3(50, 50, 0),
			glm::vec3(width, height, 360));

	int isThisOnlyWater = 50;
	while (_terrain->getHeight(value.x, value.y) < waterHeight && isThisOnlyWater > 0)
	{
		value = glm::linearRand(glm::vec3(50, 50, 0), glm::vec3(width, height, 0));
		--isThisOnlyWater;
	}
	return value;
}

void ElementsModule::SetupObject(glm::vec3 const &randomValue, std::shared_ptr<Object> obj, SObjectInfo const &objInfo)
{
	obj->SetPosition(randomValue.x, _terrain->getHeight(randomValue.y, randomValue.y), randomValue.y);
	//obj->SetRotation(0, randomValue.z, 0);
	//std::cout << "position: " << randomValue.x << " " <<
	//	randomValue.y << " " <<
	//	_terrain->getHeight(randomValue.x, randomValue.y) << std::endl;
	if (objInfo.soundPath != "")
		obj->SetSound(objInfo.soundPath, _soundSystem);
	_elements.push_back(obj);
}

void ElementsModule::createObjectsFromName(int totalElementInZone, int width, int height, SObjectInfo const &objInfo)
{
	std::shared_ptr<Object> firstObj = std::make_shared<Object>(device);
	if (firstObj->LoadMesh(objInfo.modelPath, objInfo.texturePath) == 1)
	{
		firstObj->remove();
		return;
	}
	int elemCount = objInfo.densityInPercent * totalElementInZone / 100;
	while (elemCount > 0)
	{
		glm::vec3 randomValue = getXYPos(width, height);
		if (elemCount > 1)
		{
			std::shared_ptr<Object> obj = std::make_shared<Object>(device);
			if (obj->LoadMesh(*firstObj) == 1)
			{
				return;
			}
			SetupObject(randomValue, obj, objInfo);
		}
		else
		{
			SetupObject(randomValue, firstObj, objInfo);
		}

		--elemCount;
	}
}
