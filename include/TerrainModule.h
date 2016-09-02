#pragma once

#include "AModule.h"

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _camera), _terrain(nullptr)
	{}
	~TerrainModule()
	{}

	f32 getHeight (f32 x, f32 y) const;

	virtual int init();
	virtual int update();

private:
    scene::ITerrainSceneNode *_terrain;
};
