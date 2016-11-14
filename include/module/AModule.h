#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class	Core;

class AModule
{
public:
	AModule(Core *c, IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: core(c), device(_device), camera(_camera)
	{
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		env = device->getGUIEnvironment();
	}
	~AModule()
	{}

	virtual int init() = 0;
	virtual int update() = 0;

protected:
	Core				*core;

	IrrlichtDevice		*device;
	video::IVideoDriver	*driver;
	scene::ISceneManager	*smgr;
	gui::IGUIEnvironment	*env;

	scene::ICameraSceneNode	*camera;
};
