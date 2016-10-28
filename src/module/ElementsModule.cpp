#include <algorithm>
#include <iostream>
#include <ctime>

#include "module/ElementsModule.h"
#include "Configuration.h"

float ElementsModule::getRandom(float &totalPercent, float nbElem)
{
	float maxPercent = totalPercent;
	if (maxPercent > 100.0f - nbElem * 20.0f)
		maxPercent = 100.0f - nbElem * 20.0f;
	float percent = static_cast<float>(rand() % (static_cast<int>(maxPercent) - 20)) + 20.0f;
	totalPercent -= percent;
	return percent;
}

int ElementsModule::init()
{
	float a = 100.0f, b = 100.0f, c = 100.0f;
	_objectsInfoByZone = { //first number is the density of the element in the given environment
		{
			{ getRandom(a, 3.0f), RESOURCES_PATH "/models/Rock1.obj", "", ""},
			{ getRandom(a, 3.0f), RESOURCES_PATH "/models/Tree1.obj", "", ""},
			{ a, RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg", ""}
		}, //zone 0 : mountain
		{
			{ getRandom(b, 2.0f), RESOURCES_PATH "/models/Rock2.obj", "", ""},
			{ b, RESOURCES_PATH "/models/Tree2.obj", "", ""}
		}, //zone 1 : forest
		{
			{ getRandom(c, 3.0f), RESOURCES_PATH "/models/Tree3.obj", "", RESOURCES_PATH "/sound/cicadas.mp3" },
			{ getRandom(c, 3.0f), RESOURCES_PATH "/models/Rock3.obj", "", ""},
			{ c, RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg", ""}
		} //zone 2 : beach
		};
	srand(time(0));
	putElementsOfZone(0);
	return 0;
}

void ElementsModule::putElementsOfZone(int zone)
{
	if (_elements.size() > 0)
		clear();
	for (auto const &objInfo : _objectsInfoByZone[zone])
	{
		createObjectsFromName(20, 10000, 10000, objInfo); //nbTotalElements, width, height
	}
	SetVolume(_soundVolume);
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
	_soundVolume = vol;
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
	//get position in xy between 50 and width/height and rotation angle between 0 and 360

	int isThisOnlyWater = 50;
	//while (_terrain->getHeight(value.x, value.y) < waterHeight && isThisOnlyWater > 0)
	while (0 < waterHeight && isThisOnlyWater > 0)
	{
		value = glm::linearRand(glm::vec3(50, 50, 0), glm::vec3(width, height, 0));
		--isThisOnlyWater;
	}
	return value;
}

void ElementsModule::SetupObject(glm::vec3 const &randomValue, std::shared_ptr<Object> obj, SObjectInfo const &objInfo)
{
	//obj->SetPosition(randomValue.x, _terrain->getHeight(randomValue.x, randomValue.y), randomValue.y);
	obj->SetPosition(randomValue.x, 0, randomValue.y);
	obj->SetRotation(0, randomValue.z, 0);
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
	//std::cout << ">> Number of elements " << elemCount << std::endl;
	while (elemCount > 0)
	{
		glm::vec3 randomValue = getXYPos(width, height);
		if (elemCount != objInfo.densityInPercent * totalElementInZone / 100)
		{
			std::shared_ptr<Object> obj = std::make_shared<Object>(device);
			if (obj->LoadMesh(*firstObj) == 1)
			{
				obj->remove();
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
