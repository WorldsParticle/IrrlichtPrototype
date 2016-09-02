#include "WaterModule.h"
#include "TerrainModule.h"
#include "../lib/RealisticWaterSceneNode/RealisticWater.h"
#include <iostream>

int WaterModule::init()
{
	const f32 width = 2100.0f;
	const f32 height = 2100.0f;
	irr::core::stringc resourcePath = "./lib/RealisticWaterSceneNode";

	RealisticWaterSceneNode* water = new RealisticWaterSceneNode(smgr, width, height, resourcePath);
	smgr->getRootSceneNode()->addChild(water);
	float x = 4000;
	float y = 6500;
	//y, z, x
	core::vector3df waterPosition = core::vector3df(y, _terrain->getHeight(x, y) - 580, x) + water->getPosition();
	water->setPosition(waterPosition);
	//std::cout << water->getPosition().X << " " << water->getPosition().Y << " " << water->getPosition().Z << std::endl;
}

int WaterModule::update()
{
    //nothing to do
    return 0;
}
