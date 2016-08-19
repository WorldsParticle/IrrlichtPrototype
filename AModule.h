#pragma once

#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AModule
{
public:
	AModule(IrrlichtDevice* _device,
		video::IVideoDriver* _driver,
		scene::ISceneManager* _smgr,
		gui::IGUIEnvironment* _env,
		scene::ICameraSceneNode* _camera)
		: device(_device), driver(_driver), smgr(_smgr), env(_env), camera(_camera)
	{}
	~AModule()
	{}

	virtual int init() = 0;
	virtual int update() = 0;

protected:
	IrrlichtDevice* device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIEnvironment* env;

	scene::ICameraSceneNode* camera;
};
