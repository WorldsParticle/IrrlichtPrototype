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
#include "AWeather.h"
#include <map>

class ParticleModule : public AModule
{
public:
    ParticleModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule{ _device, _camera }
    {
    }
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();
    void activate();

public:
    enum E_WEATHER { NONE, SNOW, RAIN };

private:
    irr::scene::IParticleSystemSceneNode    *_particleSystem;
    std::map<int, AWeather *>		    _weathers;
    int					    _weather = NONE;
};
