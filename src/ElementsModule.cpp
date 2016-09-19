#include "ElementsModule.h"
#include "Configuration.h"

int ElementsModule::init()
{
	Object	*testObj = new Object(device);
	Object	*testObj2 = new Object(device);

	testObj->LoadMesh(RESOURCES_PATH "/bush.3ds", RESOURCES_PATH "/bushTexture.jpg");
    testObj->SetPosition(2397 * 2, 203 * 2, 2700 * 2);
    _elements.push_back(testObj);
	testObj2->LoadMesh(RESOURCES_PATH "/tree.3ds", RESOURCES_PATH "/treeTexture.jpg");
	testObj2->SetPosition(1847 * 2, 303 * 2, 2180 * 2);
	testObj2->SetSound(RESOURCES_PATH "/drumloop.wav", _soundSystem);
	_elements.push_back(testObj2);
	return 0;
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

