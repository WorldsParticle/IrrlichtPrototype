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

#include "ParticleModule.h"
#include "SnowWeather.h"
#include "RainWeather.h"

int ParticleModule::init()
{
    // Create new ParticleSystem and disable the default Emiter
    _particleSystem = smgr->addParticleSystemSceneNode(false);
    _particleSystem->setPosition(camera->getPosition());

    // Init Emitter
    _particleSystem->setEmitter(nullptr);
    // Set Options
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

    // Init all weathers
    _weathers[NONE] = nullptr;
    _weathers[SNOW] = new SnowWeather(_particleSystem, driver);
    _weathers[RAIN] = new RainWeather(_particleSystem, driver);

    return 0;
}

int ParticleModule::update()
{
    // Nothing to do
    return 0;
}

void ParticleModule::activate()
{
    // Stuff to switch between weathers. Will be replaced by activate(weather)
    ++_weather %= _weathers.size();
    auto weather = _weathers[_weather];
    if (weather)
    {
        _particleSystem->setEmitter(weather->getEmitter());
        _particleSystem->setMaterialTexture(0, weather->getTexture());
    }
    else
        _particleSystem->setEmitter(nullptr);
}


ParticleModule::~ParticleModule()
{
    for (auto & weather : _weathers)
    {
        delete weather.second;
    }
    _weathers.clear();
}
