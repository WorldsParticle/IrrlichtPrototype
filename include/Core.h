#pragma once

#include <irrlicht.h>
#include <ISceneNode.h>
#include "driverChoice.h"
#include "WorldSettings.h"

class MyEventReceiver;
class ElementsModule;
class SkyboxModule;
class TerrainModule;
class WaterModule;
class SoundModule;
class ParticleModule;
class TimerModule;

namespace gen
{ class Generator; }

namespace map
{ class MapGraph; }

class Core
{
public:
	//Core();
	//~Core();

	int initIrrlicht();
	int initModules();
	int	initGenerator();
	void generate();
	int run();
	void close();

private:
	irr::video::IVideoDriver	*_driver;
	irr::scene::ISceneManager	*_smgr;
	irr::gui::IGUIEnvironment	*_env;

	MyEventReceiver			*_receiver;
	irr::gui::IGUITab		*_tab = NULL;

	void setGUI();


public:
	ElementsModule	*elementsModule;
	SkyboxModule	*skyboxModule;
	TerrainModule	*terrainModule;
	WaterModule		*waterModule;
	SoundModule		*soundModule;
	ParticleModule	*particleModule;
    TimerModule     *timerModule;

	irr::scene::ICameraSceneNode	*camera;
	irr::IrrlichtDevice				*device;
	gen::Generator					*generator;
	::map::MapGraph					*map;

	bool isInterfaceVisible() const;
	void toggleInterface();

	inline MyEventReceiver *eventReceiver()
	{ return _receiver; }

	void applyFogRec(irr::scene::ISceneNode *node);
};
