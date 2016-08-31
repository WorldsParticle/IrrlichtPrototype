#pragma once

#include <irrlicht.h>

class AWeather
{
public:
    virtual ~AWeather() {
        if (_emitter) _emitter->drop();
    }

public:
    auto getEmitter() { return _emitter; }
    auto getTexture() { return _texture; }
    
protected:
    irr::scene::IParticleEmitter * _emitter;
    irr::video::ITexture * _texture;
};
