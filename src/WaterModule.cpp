#include "WaterModule.h"
#include "TerrainModule.h"
#include "RealisticWater.h"
#include "Configuration.h"
#include "water/WaterNode.h"
#include <iostream>

WaterModule::WaterModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain) :
	AModule{ _device, _camera }, _terrain(terrain), _waterNodes(std::list<WaterNode *>())
{

}

int WaterModule::init()
{
	WaterNode *w = new WaterNode (smgr->getRootSceneNode(), smgr,
                                                    core::vector3df(4900, 300, 4900),
                                                    core::vector2df(98000, 98000));


	_waterNodes.push_back(w);
  smgr->getRootSceneNode()->addChild(w);

	return true;
}

int WaterModule::update()
{
	return true;
}
