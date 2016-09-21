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

#include "AModule.h"

class TerrainModule;

class WaterModule : public AModule
{
    public:
	WaterModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera, TerrainModule *terrain)
	    : AModule{ _device, _camera }, _terrain(terrain)
	{
	}
	~WaterModule();
	virtual int init();
	virtual int update();
    private:
	TerrainModule *_terrain;
};
