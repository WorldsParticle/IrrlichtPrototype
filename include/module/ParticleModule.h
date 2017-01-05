#pragma once

#include "module/AModule.h"
#include "module/TimerModule.h"
#include "scene/weather/AWeather.h"
#include <map>

class ParticleModule : public AModule
{
public:
    ParticleModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera,
		TimerModule * timer)
        : AModule(c, _device, _camera),
        _particleSystem(nullptr),
        _weather(AWeather::E_WEATHER::NONE),
        _timer(timer)

    {
    }
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();

    void setWeather(int w);
    void setWeatherIntensity(int i);


private:
    irr::scene::IParticleSystemSceneNode * _particleSystem;
    std::map<int, AWeather *>		       _weathers;
    AWeather::E_WEATHER                    _weather;

    TimerModule * _timer;
    irr::u32      _updateSpeed;
    irr::u32      _nextUpdate;
};
