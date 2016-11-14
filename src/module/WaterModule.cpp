#include "module/WaterModule.h"
#include "module/TerrainModule.h"
#include "scene/water/RealisticWater.h"
#include "Configuration.h"
#include "WorldSettings.h"
#include "scene/water/WaterNode.h"
#include <iostream>

WaterModule::WaterModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain) :
	AModule(c, _device, _camera), _terrain(terrain), _waterNodes(std::list<WaterNode *>())
{

}

WaterModule::~WaterModule()
{
	for (WaterNode *n : _waterNodes)
		delete n;
}

int WaterModule::init()
{
	WaterNode *w = new WaterNode(smgr->getRootSceneNode(), smgr, 
		//ORIGIN_POS + core::vector3df(0, WATER_HEIGHT, 0), core::vector2df(MAP_SIZE, MAP_SIZE));
                                                    core::vector3df((512 * 500) / 2 - 512, WATER_HEIGHT, (512 * 500) / 2 - 512),
                                                    core::vector2df((512 * 500) * 2, (512 * 500) * 2));


	_waterNodes.push_back(w);
  smgr->getRootSceneNode()->addChild(w);

	return true;
}

int WaterModule::update()
{
	return true;
}
