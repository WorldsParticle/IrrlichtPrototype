#pragma once

#include "AModule.h"

class TerrainModule;
class WaterNode;
//class IAnimatedMesh;
//class ISceneNode;

class WaterModule : public AModule
{
    public:
	WaterModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain);
	~WaterModule();
	virtual int init();
	virtual int update();

    private:


	TerrainModule *_terrain;
  WaterNode     *_water;

};
