//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) WorldsParticle
//

#include "WaterModule.h"
#include "TerrainModule.h"
#include "RealisticWater.h"
#include "Configuration.h"
#include <iostream>

int WaterModule::init()
{
	const f32 width = 2100.0f;
	const f32 height = 2100.0f;
	irr::core::stringc resourcePath = RESOURCES_PATH;

	RealisticWaterSceneNode* water = new RealisticWaterSceneNode(smgr, width, height, resourcePath);
	smgr->getRootSceneNode()->addChild(water);
	float x = 4000;
	float y = 6500;
	//y, z, x
	core::vector3df waterPosition = core::vector3df(y, _terrain->getHeight(x, y) - 580, x) + water->getPosition();
	water->setPosition(waterPosition);

	//Create mesh to add water effect to
	//IAnimatedMesh* plane = smgr->addHillPlaneMesh("plane", // Name of mesh
	//		core::dimension2d<f32>(20,20), //   Size of a tile of the mesh. (10.0f, 10.0f) would be a good value to start, for example. 
	//		core::dimension2d<u32>(40,40), 0, 0, //	Specifies how much tiles there will be. If you specifiy for example that a tile has the size (10.0f, 10.0f) and the tileCount is (10,10), than you get a field of 100 tiles which has the dimension 100.0fx100.0f. 
	//		core::dimension2d<f32>(0,0), //material 
	//		core::dimension2d<f32>(10,10)); //countHills 

	//mesh, waveheight = 0.5f, wave speed = 350.0f, wave length = 80.0f
	//ISceneNode* sea = smgr->addWaterSurfaceSceneNode(plane->getMesh(0), 5.0f, 300.0f, 40.0f);
	//sea->setMaterialTexture(0, driver->getTexture("../../media/stones.jpg"));
	//sea->setMaterialTexture(1, driver->getTexture("../../media/water.jpg"));
	//sea->setMaterialFlag(EMF_LIGHTING, true);
	//sea->setMaterialType(video::EMT_REFLECTION_2_LAYER);
	std::cout << water->getPosition().X << " " << water->getPosition().Y << " " << water->getPosition().Z << std::endl;
	return 0;
}

int WaterModule::update()
{
    //nothing to do
    return 0;
}
