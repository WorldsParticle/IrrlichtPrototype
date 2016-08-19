#pragma once

#include "AModule.h"

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device,
		video::IVideoDriver* _driver,
		scene::ISceneManager* _smgr,
		gui::IGUIEnvironment* _env,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _driver, _smgr, _env, _camera)
	{}
	~TerrainModule()
	{}

	virtual int init();
	virtual int update();

private:

};
