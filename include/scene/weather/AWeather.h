#pragma once

#include <irrlicht.h>
#include <map>


class AWeather
{
public:
    AWeather() {}
    virtual ~AWeather()
    {
        if (_emitter)
		    _emitter->drop();
    }

public:
    enum E_WEATHER { NONE, RAIN, SNOW };
    enum E_INTENSITY { ZERO, LOW, MEDIUM, HIGH };

public:
    virtual void update(E_INTENSITY intensity) = 0;
    void setWeather(irr::scene::IParticleSystemSceneNode * ps,
                    E_INTENSITY intensity);


protected:
    void updateEmitter(int minPart, int maxPart, irr::core::vector3df direction);

protected:
    irr::scene::IParticleEmitter * _emitter;
    irr::video::ITexture	     * _texture;
};
