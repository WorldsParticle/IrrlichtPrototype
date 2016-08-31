#pragma once

#pragma once

#include "AWeather.h"

class RainWeather : public AWeather
{
public:
    RainWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
        irr::video::IVideoDriver * driver);

    virtual ~RainWeather() = default;
};