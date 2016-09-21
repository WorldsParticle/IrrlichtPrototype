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

class AWeather
{
public:
    virtual ~AWeather()
    {
        if (_emitter)
		_emitter->drop();
    }

public:
	irr::scene::IParticleEmitter * getEmitter() const
    {
	    return _emitter;
    }
	irr::video::ITexture * getTexture() const
    {
	    return _texture;
    }

protected:
    irr::scene::IParticleEmitter    *_emitter;
    irr::video::ITexture	    *_texture;
};
