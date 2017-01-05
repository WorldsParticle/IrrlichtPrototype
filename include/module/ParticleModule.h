#pragma once

#include "module/AModule.h"
#include "module/TimerModule.h"
#include "scene/weather/AWeather.h"
#include <map>
#include <vector>

class ParticleModule : public AModule
{
public:
    ParticleModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera,
        TimerModule * timer)
        : AModule(c, _device, _camera),
        _particleSystem(nullptr),
        _IGWeather(AWeather::E_WEATHER::NONE),
        _IGWeathers(std::vector<int> {AWeather::E_WEATHER::NONE}),
        _weatherIntensity(AWeather::E_INTENSITY::LOW),
        _timer(timer)

    {
    }
    ~ParticleModule();

public:
    virtual int init();
    virtual int update();

    void setWeather(int w, int intensity);
    

private:
    void changeWeather();

    void updateWeather();
    void updateIntensity();

    void increaseIntensity();
    void decreaseIntensity();

    void previousWeather();
    void nextWeather();

private:
    irr::scene::IParticleSystemSceneNode * _particleSystem;

    std::map<int, AWeather *> _weathers;     // Weather map with all weathers

    AWeather::E_INTENSITY _weatherIntensity;
    std::vector<int>      _IGWeathers;       // In Game list of weathers set by the user
    int                   _IGWeather;        // In Game current weather index. To get "True" weather do _IGWeathers[_IGWeather]

    TimerModule * _timer;
    irr::u32      _updateSpeed;
    irr::u32      _nextUpdate;
};
