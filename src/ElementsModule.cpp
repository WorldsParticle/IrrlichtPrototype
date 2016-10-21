#include <algorithm>
#include <iostream>

#include "ElementsModule.h"
#include "Configuration.h"

int ElementsModule::init()
{
	srand(time(0));
	createObjectsFromName(30, 10000, 10000, 34, RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg", "");
	createObjectsFromName(30, 10000, 10000, 33, RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg", RESOURCES_PATH "/sound/drumloop.wav");
	createObjectsFromName(30, 10000, 10000, 33, RESOURCES_PATH "/models/Rock1.obj", "", "");
	//testObj3->LoadMesh(RESOURCES_PATH "/models/Rock1.obj", "");
	//testObj3->SetScale(10, 10, 10);
	return 0;
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

void ElementsModule::SetVolume(float vol)
{
	for (Object *elem : _elements)
	{
		elem->SetVolume(vol);
	}
}

static float calcPosition(float i, float size, float elemCount)
{
    float position = i * size / elemCount;

    int offsetMax = static_cast<int>(size / 2.0f, elemCount);
    int offset = rand() % offsetMax - (offsetMax / 2);
    position += static_cast<float>(offset);

    return position;
}

void ElementsModule::createObjectsFromName(int totalElementInZone, int width, int height, int density, std::string const &modelPath, std::string const &texturePath, std::string const &soundPath)
{
	int elemCount = density * totalElementInZone / 100;
	//int elemCountSide = static_cast<int>(std::sqrt(elemCount));
	while (elemCount > 0)
	{
		float x = rand() % width;
		float y = rand() % height;
		Object *obj = new Object(device);
		if (obj->LoadMesh(modelPath, texturePath) == 1)
		{
			delete obj;
			return;
		}

		obj->SetPosition(x, _terrain->getHeight(x, y), y);
		//TODO: random rotate
		std::cout << "position: " << x << " " << y << " " << _terrain->getHeight(x, y) << std::endl;
		if (soundPath != "")
			obj->SetSound(soundPath, _soundSystem);
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
