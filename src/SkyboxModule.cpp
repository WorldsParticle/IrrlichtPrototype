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

#include "SkyboxModule.h"
#include "Configuration.h"

int SkyboxModule::init()
{
	// add a nice skybox

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	_skybox = smgr->addSkyBoxSceneNode(
		driver->getTexture(RESOURCES_PATH "/irrlicht2_up.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_dn.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_lf.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_rt.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_ft.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_bk.jpg"));

	_skydome = smgr->addSkyDomeSceneNode(driver->getTexture(RESOURCES_PATH "/skydome.jpg"), 16, 8, 0.95f, 2.0f);

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	activeNight(false);

	return 0;
}

int SkyboxModule::update()
{
	//nothing to do
	return 0;
}

void SkyboxModule::activeNight(bool n)
{
	_night = n;
	_skybox->setVisible(!_night);
	_skydome->setVisible(_night);
}
