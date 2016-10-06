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
    void setWeather(irr::scene::IParticleSystemSceneNode * ps)
    {
        ps->setEmitter(_emitter);
        ps->setMaterialTexture(0, _texture);
    }

public:
    enum E_WEATHER { NONE, RAIN, SNOW };


protected:
    irr::scene::IParticleEmitter * _emitter;
    irr::video::ITexture	     * _texture;
};
