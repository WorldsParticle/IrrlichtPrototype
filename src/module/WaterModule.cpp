#include "module/WaterModule.h"
#include "module/TerrainModule.h"
#include "scene/water/RealisticWater.h"
#include "Configuration.h"
#include "WorldSettings.h"
#include "scene/water/WaterNode.h"
#include "Core.h"
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
                                                    core::vector3df(WP_TERRAIN_SIZE / 2, WP_SEA_HEIGHT, WP_TERRAIN_SIZE / 2),
                                                    core::vector2df(WP_SEA_SIZE, WP_SEA_SIZE));

	_waterNodes.push_back(w);
  smgr->getRootSceneNode()->addChild(w);

	return true;
}

int WaterModule::update()
{
	// Temporary
	static core::vector3df correctPos(0, WP_SEA_HEIGHT + 1, 0); // CAREFULL, this will fail if cam start under water


	const core::vector3df &pos = smgr->getActiveCamera()->getAbsolutePosition();
	if (pos.Y  < WP_SEA_HEIGHT + 1)
		smgr->getActiveCamera()->setPosition(correctPos);
	else
		correctPos = pos;
	return true;
}
