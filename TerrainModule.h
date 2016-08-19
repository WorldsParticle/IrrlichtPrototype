#pragma once

#include "AModule.h"

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _camera)
	{}
	~TerrainModule()
	{}

	virtual int init();
	virtual int update();

private:

};
