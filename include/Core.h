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

#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

class MyEventReceiver;
class ElementsModule;
class SkyboxModule;
class TerrainModule;
class WaterModule;
class SoundModule;
class ParticleModule;

class Core
{
public:
	//Core();
	//~Core();

	int initIrrlicht();
	int initModules();
	int run();
	void close();

private:
	irr::video::IVideoDriver	*_driver;
	irr::scene::ISceneManager	*_smgr;
	irr::gui::IGUIEnvironment	*_env;

	MyEventReceiver			*_receiver;

public:
	ElementsModule			*elementsModule;
	SkyboxModule			*skyboxModule;
	TerrainModule			*terrainModule;
	WaterModule			*waterModule;
	SoundModule			*soundModule;
	ParticleModule			*particleModule;
	bool				isInterfaceActive = false;
	irr::scene::ICameraSceneNode	*camera;
	irr::IrrlichtDevice		*device;

};

