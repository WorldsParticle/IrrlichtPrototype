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
	// Such a magnificient horror
    const::vector3df  &pos = camera->getAbsolutePosition();

		if (pos.X > 5400.0f && pos.X < 7500.0f &&
				pos.Z > 3200.0f && pos.Z < 4600.0f)
				{
						const::vector3df &rPos = camera->getPosition();
						float	x = pos.X;
						float z = pos.Z;

						if (pos.X > 5400.0f && pos.X < 5500.0f)
							x = 5400;
						else if (pos.X > 7400 && pos.X < 7500)
						  x = 7500;

						if (pos.Z > 3200.0f && pos.Z < 3300.0f)
								z = 3200;
						else if (pos.Z > 4500 && pos.Z < 4600)
							  z = 4600;

					  camera->setPosition(vector3df(x - pos.X + rPos.X, rPos.Y, z - pos.Z + rPos.Z));
				}

    return 0;
}
