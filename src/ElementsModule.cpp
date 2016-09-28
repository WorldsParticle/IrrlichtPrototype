#include "ElementsModule.h"
#include "Configuration.h"

int ElementsModule::init()
{
	Object	*testObj = new Object(device);
	Object	*testObj2 = new Object(device);
	Object	*testObj3 = new Object(device);

	testObj->LoadMesh(RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg");
    testObj->SetPosition(2397 * 2, 203 * 2, 2700 * 2);
    _elements.push_back(testObj);
	testObj2->LoadMesh(RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg");
	testObj2->SetPosition(1847 * 2, 303 * 2, 2180 * 2);
	testObj2->SetSound(RESOURCES_PATH "/drumloop.wav", _soundSystem);
	_elements.push_back(testObj2);

	testObj3->LoadMesh(RESOURCES_PATH "/models/Rock1.obj", "");
	testObj3->SetPosition(1000, 500, 1000);
	testObj3->SetRotation(90, 0, 0);
	//testObj3->SetScale(10, 10, 10);
	_elements.push_back(testObj3);
	return 0;
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

