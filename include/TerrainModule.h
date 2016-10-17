#pragma once

#include <string>
#include "AModule.h"

class bitmap_image;

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _camera), _terrain(nullptr), _anim(nullptr), _path(""), _heightmapImage(nullptr)
	{
	}
	~TerrainModule()
	{
	}

	f32 getHeight (f32 x, f32 y) const;

	virtual int init();
	virtual int update();
    void generate(int size = 513, int seed = 0);
    void generateRadial(int size = 513, int seed = 0);
	void setHeightmap();

private:
    scene::ITerrainSceneNode    *_terrain;
    scene::ISceneNodeAnimator   *_anim;
    std::string                 _path;
	bitmap_image *				_heightmapImage;
};
