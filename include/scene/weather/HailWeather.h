#pragma once

#include "AWeather.h"

class HailWeather : public AWeather
{
public:
    HailWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
        irr::video::IVideoDriver * driver);

    virtual ~HailWeather() = default;

public:
    virtual void update(E_INTENSITY intensity);
};
