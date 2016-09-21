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

#include "RainWeather.h"
#include "Configuration.h"

RainWeather::RainWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                         irr::video::IVideoDriver * driver)
{
    // Create new BoxEmiter
    _emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5000, 1200, -5000, 5000, 1200, 5000),    // Coordinates
        irr::core::vector3df(0.0f, -1.0f, 0.0f),                                // Direction
        2000, 2200,                                                             // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        1200, 1500,                                                             // Min/Max LifeTime
        5,                                                                      // Angle deviation
        irr::core::dimension2df(10.0f, 10.0f),                                  // Size min
        irr::core::dimension2df(15.0f, 15.0f));                                 // Size max

    _texture = driver->getTexture(RESOURCES_PATH "/one_drop.png");
}
