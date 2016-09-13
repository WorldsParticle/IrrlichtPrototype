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
	irr::scene::IParticleEmitter * getEmitter() const
    {
	    return _emitter;
    }
	irr::video::ITexture * getTexture() const
    {
	    return _texture;
    }

protected:
    irr::scene::IParticleEmitter    *_emitter;
    irr::video::ITexture	    *_texture;
};
