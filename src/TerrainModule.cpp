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

#include "TerrainModule.h"
#include "Configuration.h"

int TerrainModule::init()
{
	// add terrain scene node
	_terrain = smgr->addTerrainSceneNode(
        RESOURCES_PATH "/terrain-heightmap.bmp",
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
		driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
	_terrain->setMaterialTexture(1,
		driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));

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
