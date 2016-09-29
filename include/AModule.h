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
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class AModule
{
public:
	AModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: device(_device), camera(_camera)
	{
		driver = device->getVideoDriver();
		smgr = device->getSceneManager();
		env = device->getGUIEnvironment();
	}
	~AModule()
	{}

	virtual int init() = 0;
	virtual int update() = 0;

protected:
	IrrlichtDevice		*device;
	video::IVideoDriver	*driver;
	scene::ISceneManager	*smgr;
	gui::IGUIEnvironment	*env;

	scene::ICameraSceneNode	*camera;
};
