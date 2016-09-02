#pragma once

#include <irrlicht.h>
#include "driverChoice.h"
#include "MyEventReceiver.h"
#include "ElementsModule.h"
#include "SkyboxModule.h"
#include "TerrainModule.h"
#include "WaterModule.h"
#include "SoundModule.h"
#include "ParticleModule.h"

class Core
{
public:
	//Core();
	//~Core();

	int initIrrlicht();
	int initModules();
	int run();
	void close();

private:

	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;

	scene::ICameraSceneNode* camera;

	MyEventReceiver *receiver;

public:
	ElementsModule *elementsModule;
	SkyboxModule *skyboxModule;
	TerrainModule *terrainModule;
	WaterModule *waterModule;
	SoundModule *soundModule;
    ParticleModule *particleModule;

};

