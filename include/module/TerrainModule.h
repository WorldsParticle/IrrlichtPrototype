#pragma once

#include <list>
#include <vector>
#include <string>
#include "AModule.h"

class bitmap_image;
namespace map
{
class MapGraph;
}

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera);
	~TerrainModule();

	inline std::vector<scene::ITerrainSceneNode *>  &terrainGridNodes()
	{ return _terrainGridNodes; }
	inline std::vector<scene::ISceneNodeAnimator *>  &terrainGridAnims()
	{ return _terrainGridAnims; }

	virtual int init();
	virtual int update();

	void generateFromMap(::map::MapGraph *mapGraph);
    void clearNodes();

    float   getHeight(irr::f32 x, irr::f32 z);

private:

    // should be in a std::pair
    std::vector<scene::ITerrainSceneNode *>		_terrainGridNodes;
    std::vector<scene::ISceneNodeAnimator *>	_terrainGridAnims;
};
