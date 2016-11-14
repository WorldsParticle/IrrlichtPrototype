#pragma once

#include "AModule.h"
#include "scene/weather/AWeather.h"
#include <map>

class ParticleModule : public AModule
{
public:
    ParticleModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule(c, _device, _camera),
        _particleSystem(nullptr),
        _weathers(),
        _weather(AWeather::E_WEATHER::NONE)
    {
    }
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();
    void setWeather(int w);


private:
    irr::scene::IParticleSystemSceneNode * _particleSystem;
    std::map<int, AWeather *>		           _weathers;
    AWeather::E_WEATHER                    _weather;
};
