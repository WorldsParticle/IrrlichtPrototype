#pragma once

#include "AModule.h"
#include "AWeather.h"
#include <map>

class ParticleModule : public AModule
{
public:
    ParticleModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule{ _device, _camera }
    {}
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();
    void activate();

public:
    enum E_WEATHER { NONE, SNOW, RAIN };

private:
    irr::scene::IParticleSystemSceneNode * _particleSystem;
    std::map<int, AWeather *> _weathers;
    int _weather = NONE;
};