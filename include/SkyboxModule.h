#pragma once

#include "AModule.h"

class SkyboxModule : public AModule
{
public:
	SkyboxModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device,  _camera),
		_night(false)
	{
	}
	~SkyboxModule()
	{
	}

	virtual int init();
	virtual int update();

	void activeNight(bool n);

private:
	bool		    _night;

	scene::ISceneNode   *_skybox;
	scene::ISceneNode   *_skydome;
};
