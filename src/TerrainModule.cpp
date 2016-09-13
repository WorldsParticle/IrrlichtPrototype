#include "TerrainModule.h"

int TerrainModule::init()
{
	// add terrain scene node
	_terrain = smgr->addTerrainSceneNode(
		"./ressources/terrain-heightmap.bmp",
		0,                  // parent node
		-1,                 // node id
		core::vector3df(0.f, 0.f, 0.f),     // position
		core::vector3df(0.f, 0.f, 0.f),     // rotation
		core::vector3df(40.f, 4.4f, 40.f),  // scale
		video::SColor(255, 255, 255, 255),   // vertexColor
		5,                  // maxLOD
		scene::ETPS_17,             // patchSize
		4                   // smoothFactor
		);

	_terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	_terrain->setMaterialTexture(0,
		driver->getTexture("./ressources/terrain-texture.jpg"));
	_terrain->setMaterialTexture(1,
		driver->getTexture("./ressources/detailmap3.jpg"));

	_terrain->setMaterialType(video::EMT_DETAIL_MAP);

	_terrain->scaleTexture(1.0f, 20.0f);


	// create triangle selector for the terrain
	scene::ITriangleSelector* selector
		= smgr->createTerrainTriangleSelector(_terrain, 0);
	_terrain->setTriangleSelector(selector);

	// create collision response animator and attach it to the camera
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, camera, core::vector3df(60, 100, 60),
		core::vector3df(0, 0, 0),
		core::vector3df(0, 50, 0));
	selector->drop();
	camera->addAnimator(anim);
	anim->drop();
	return 0;
}

int TerrainModule::update()
{
	//nothing to do
	return 0;
}

f32 TerrainModule::getHeight(f32 x, f32 y) const
{
    return _terrain->getHeight(x, y);
}
