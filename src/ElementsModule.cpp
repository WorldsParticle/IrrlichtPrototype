#include "ElementsModule.h"

int ElementsModule::init(){

	Object	*testObj = new Object(device);
	Object	*testObj2 = new Object(device);

	testObj->LoadMesh("./ressources/sydney.md2", "./ressources/sydney.bmp");
    testObj->SetPosition(2397 * 2, 343 * 2, 2700 * 2);
    _elements.push_back(testObj);
	testObj2->LoadMesh("./ressources/sydney.md2", "./ressources/sydney.bmp");
	testObj2->SetPosition(1847 * 2, 323 * 2, 2680 * 2);
	testObj2->SetSound("./ressources/drumloop.wav", _soundSystem);
	_elements.push_back(testObj2);
	return 0;
}
int ElementsModule::update(){
	//nothing to do
	return 0;
}

