#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

class MyEventReceiver;
class ElementsModule;
class SkyboxModule;
class TerrainModule;
class WaterModule;
class SoundModule;
class ParticleModule;

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
	irr::video::IVideoDriver	*_driver;
	irr::scene::ISceneManager	*_smgr;
	irr::gui::IGUIEnvironment	*_env;

	MyEventReceiver			*_receiver;

public:
	ElementsModule			*elementsModule;
	SkyboxModule			*skyboxModule;
	TerrainModule			*terrainModule;
	WaterModule			*waterModule;
	SoundModule			*soundModule;
	ParticleModule			*particleModule;
	bool				isInterfaceActive = false;
	irr::scene::ICameraSceneNode	*camera;
	irr::IrrlichtDevice		*device;

};

