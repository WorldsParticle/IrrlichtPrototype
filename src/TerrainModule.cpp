#include "TerrainModule.h"

int TerrainModule::init(){

	// add terrain scene node
	scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
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

	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	terrain->setMaterialTexture(0,
		driver->getTexture("./ressources/terrain-texture.jpg"));
	terrain->setMaterialTexture(1,
		driver->getTexture("./ressources/detailmap3.jpg"));

	terrain->setMaterialType(video::EMT_DETAIL_MAP);

	terrain->scaleTexture(1.0f, 20.0f);


	// create triangle selector for the terrain 
	scene::ITriangleSelector* selector
		= smgr->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(selector);

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
int TerrainModule::update(){
	//nothing to do
	return 0;
}

