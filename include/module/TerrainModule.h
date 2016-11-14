#pragma once

#include <list>
#include <vector>
#include <string>
#include "AModule.h"
#include "map/map.h"

class bitmap_image;

class TerrainModule : public AModule
{
public:
	TerrainModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera);
	~TerrainModule();

	inline std::vector<scene::ITerrainSceneNode *>  &terrainGridNodes()
	{ return _terrainGridNodes; }
	inline std::vector<scene::ISceneNodeAnimator *>  &terrainGridAnims()
	{ return _terrainGridAnims; }

	virtual int init();
	virtual int update();

	void generateFromMap(::map::MapGraph &mapGraph);
  void clearNodes();

  float   getHeight(irr::f32 x, irr::f32 z);

private:
	scene::ITerrainSceneNode	*loadTerrain(::map::MapGraph &map, unsigned int x, unsigned int z, float scale);

    // should be in a std::pair
  std::vector<scene::ITerrainSceneNode *>		_terrainGridNodes;
  std::vector<scene::ISceneNodeAnimator *>	_terrainGridAnims;
};
