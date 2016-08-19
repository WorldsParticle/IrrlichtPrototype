#pragma once

#include <irrlicht.h>
#include "driverChoice.h"
#include "MyEventReceiver.h"

class Core
{
public:
	//Core();
	//~Core();

	int initIrrlicht();
	int initModules();
	int run();
	void drop();

private:

	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;

	//scene::ITerrainSceneNode* terrain;
	scene::ICameraSceneNode* camera;

};

