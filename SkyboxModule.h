#pragma once

#include "AModule.h"

class SkyboxModule : public AModule
{
public:
	SkyboxModule(IrrlichtDevice* _device,
		video::IVideoDriver* _driver,
		scene::ISceneManager* _smgr,
		gui::IGUIEnvironment* _env,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _driver, _smgr, _env, _camera)
	{}
	~SkyboxModule()
	{}

	virtual int init();
	virtual int update();

private:

};
