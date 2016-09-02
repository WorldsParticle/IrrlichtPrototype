#pragma once

#include "AModule.h"

class TerrainModule;

class WaterModule : public AModule
{
    public:
	WaterModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain)
	    : AModule{ _device, _camera }, _terrain(terrain)
	{}
	~WaterModule();
	virtual int init();
	virtual int update();
    private:
	TerrainModule *_terrain;
};
