#pragma once

#include "AModule.h"
#include "AWeather.h"
#include <map>

class ParticleModule : public AModule
{
public:
    ParticleModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule{ _device, _camera },
        _weather(AWeather::E_WEATHER::NONE),
        _particleSystem(nullptr)
    {
    }
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();
    void activate();


private:
    int     _weather;
    irr::scene::IParticleSystemSceneNode * _particleSystem;
    std::map<int, AWeather *>		       _weathers;
};
