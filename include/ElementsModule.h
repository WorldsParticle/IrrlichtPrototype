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

#include <list>
#include "AModule.h"
#include "Object.h"

class ElementsModule : public AModule
{
public:
	ElementsModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera, FMOD::System *sndSystem)
		: AModule(_device, _camera), _soundSystem(sndSystem)
	{}
	~ElementsModule()
	{}

	virtual int init();
	virtual int update();

private:
    list<Object *>	_elements;
	FMOD::System	*_soundSystem;
};
