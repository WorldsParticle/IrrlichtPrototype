#pragma once

#include <list>
#include "AModule.h"

class TerrainModule;
class WaterNode;
//class IAnimatedMesh;
//class ISceneNode;

class WaterModule : public AModule
{
    public:
	WaterModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain);
	~WaterModule();
inline std::list<WaterNode *>  &waterNodes()
{ return _waterNodes; }

	virtual int init();
	virtual int update();

    private:


	TerrainModule          *_terrain;
  std::list<WaterNode *>  _waterNodes;

};
