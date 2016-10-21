#include <algorithm>
#include <iostream>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>

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
	//createObjectsFromName(30, 10000, 10000, 34, RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg", "");
	//createObjectsFromName(30, 10000, 10000, 33, RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg", RESOURCES_PATH "/sound/drumloop.wav");
	//createObjectsFromName(30, 10000, 10000, 33, RESOURCES_PATH "/models/Rock1.obj", "", "");
	//testObj3->LoadMesh(RESOURCES_PATH "/models/Rock1.obj", "");
	//testObj3->SetScale(10, 10, 10);
	return 0;
}

void ElementsModule::putElementsOfZone(int zone)
{
	if (_elements.size() > 0)
		clear();
	for (auto const &objInfo : _objectsInfoByZone[zone])
	{
		createObjectsFromName(100, 10000, 10000, objInfo);
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

static float calcPosition(float i, float size, float elemCount)
{
    float position = i * size / elemCount;

    int offsetMax = static_cast<int>(size / 2.0f);//, elemCount);
    int offset = rand() % offsetMax - (offsetMax / 3);
    position += static_cast<float>(offset);

    return position;
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
	//int elemCountSide = static_cast<int>(std::sqrt(elemCount));
	while (elemCount > 0)
	{
		//float x = rand() % width;
		//float y = rand() % height;
		std::cout << "position max : " << width << " " << height << std::endl;
		glm::vec3 value = glm::gaussRand(
			glm::vec3(0, 0, 0),
			glm::vec3(100 / 2, 0, 100 / 2));
		std::cout << "value : " << value.x << " " << value.z << std::endl;

		float x = value.x;
		float y = value.z;
		std::shared_ptr<Object> obj = std::make_shared<Object>(device);
		if (obj->LoadMesh(*firstObj) == 1)
		{
			obj->remove();
			return;
		}

		obj->SetPosition(x, _terrain->getHeight(x, y), y);
		//TODO: random rotate
		std::cout << "position: " << x << " " << y << " " << _terrain->getHeight(x, y) << std::endl;
		if (objInfo.soundPath != "")
			obj->SetSound(objInfo.soundPath, _soundSystem);
		_elements.push_back(obj);
		--elemCount;
	}
	//for (int i = 0; i < height; i++)
	//{
	//	float x = calcPosition(i, width, elemCountSide);

	//	for (int j = 0; j < width; j++)
	//	{
	//		float y = calcPosition(j, height, elemCountSide);

	//		Object *obj = new Object(device);
	//		if (obj->LoadMesh(modelPath, texturePath) == 1)
	//		{
	//			delete obj;
	//			return;
	//		}

	//		obj->SetPosition(x, _terrain->getHeight(x, y), y);
	//		//TODO: random rotate
	//		std::cout << "position: " << x << " " << y << " " << _terrain->getHeight(x, y) << std::endl;
	//		if (soundPath != "")
	//			obj->SetSound(soundPath, _soundSystem);
	//		_elements.push_back(obj);
	//	}
	//}
}
