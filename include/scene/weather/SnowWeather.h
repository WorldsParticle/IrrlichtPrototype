#pragma once

#include "AWeather.h"

class SnowWeather : public AWeather
{
public:
    SnowWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                irr::video::IVideoDriver * driver);

    virtual ~SnowWeather() = default;

public:
    virtual void update(E_INTENSITY intensity);
};
