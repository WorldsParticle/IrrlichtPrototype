#pragma once

#include <irrlicht.h>
#include <map>


class AWeather
{
public:
    AWeather() :
        _intensity(WeatherIntensity::LOW)
    {}
    virtual ~AWeather()
    {
        if (_emitter)
		    _emitter->drop();
    }

public:
    void update(irr::scene::IParticleSystemSceneNode * ps);
    void setWeather(irr::scene::IParticleSystemSceneNode * ps);
    void setWeatherIntensity(irr::scene::IParticleSystemSceneNode *ps, int i);

public:
    enum E_WEATHER { NONE, RAIN, SNOW };


protected:
    virtual void updateWeather() {}

    void increaseIntensity(irr::scene::IParticleSystemSceneNode * ps);
    void decreaseIntensity(irr::scene::IParticleSystemSceneNode * ps);
    void updateEmitter(int minPart, int maxPart, irr::core::vector3df direction);

protected:
    enum WeatherIntensity { ZERO, LOW, MEDIUM, HIGH };

    WeatherIntensity               _intensity;
    irr::scene::IParticleEmitter * _emitter;
    irr::video::ITexture	     * _texture;
};
