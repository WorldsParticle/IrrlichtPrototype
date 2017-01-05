#pragma once

#include "AWeather.h"

class RainWeather : public AWeather
{
public:
    RainWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
        irr::video::IVideoDriver * driver);

    virtual ~RainWeather() = default;

public:
    virtual void update(E_INTENSITY intensity);
};
