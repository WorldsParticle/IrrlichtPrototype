#include "WaterModule.h"
#include "TerrainModule.h"
#include "RealisticWater.h"
#include "Configuration.h"
#include "water/WaterNode.h"
#include <iostream>

WaterModule::WaterModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain) :
	AModule{ _device, _camera }, _terrain(terrain), _water(nullptr)
{

}

int WaterModule::init()
{
	_water = new WaterNode (smgr->getRootSceneNode(), smgr,
													core::vector3df(4900, 300, 4900),
													core::vector2df(9800, 9800));

  smgr->getRootSceneNode()->addChild(_water);

	return true;
}

int WaterModule::update()
{
	return true;
}
