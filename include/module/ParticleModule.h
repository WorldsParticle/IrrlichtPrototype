#pragma once

#include "AModule.h"
#include "scene/weather/AWeather.h"
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
    void setWeather(int w);


private:
    irr::scene::IParticleSystemSceneNode * _particleSystem;
    std::map<int, AWeather *>		       _weathers;
    AWeather::E_WEATHER                    _weather;

    irr::ITimer * _timer;
    irr::u32      _updateSpeed;
    irr::u32      _nextUpdate;
};
