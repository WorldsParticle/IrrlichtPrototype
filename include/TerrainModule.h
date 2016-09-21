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

#include <string>
#include "AModule.h"

class bitmap_image;

class TerrainModule : public AModule
{
public:
	TerrainModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _camera), _terrain(nullptr), _anim(nullptr), _path(""), _heightmapImage(nullptr)
	{
	}
	~TerrainModule()
	{
	}

	f32 getHeight (f32 x, f32 y) const;

	virtual int init();
	virtual int update();
    void generate(int size = 513, int seed = 0);
	void setHeightmap();

private:
    scene::ITerrainSceneNode    *_terrain;
    scene::ISceneNodeAnimator   *_anim;
    std::string                 _path;
	bitmap_image *				_heightmapImage;
};
