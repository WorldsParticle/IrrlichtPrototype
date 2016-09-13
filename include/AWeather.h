#pragma once

#include <irrlicht.h>

class AWeather
{
public:
    virtual ~AWeather() {
        if (_emitter) _emitter->drop();
    }

public:
	irr::scene::IParticleEmitter * getEmitter() { return _emitter; }
	irr::video::ITexture * getTexture() { return _texture; }
    
protected:
    irr::scene::IParticleEmitter * _emitter;
    irr::video::ITexture * _texture;
};
