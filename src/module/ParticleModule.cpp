#include "module/ParticleModule.h"
#include "scene/weather/SnowWeather.h"
#include "scene/weather/RainWeather.h"

// Weather update speed in sec
#define     WEATHER_UPDATE_SPEED  10

int ParticleModule::init()
{
    // Create new ParticleSystem and disable the default Emiter
    _particleSystem = smgr->addParticleSystemSceneNode(false);
    _particleSystem->setParent(camera);

    // Init Emitter
    _particleSystem->setEmitter(nullptr);
    // Set Options
    _particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    _particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

    // Init all weathers
    _weathers[AWeather::E_WEATHER::NONE] = nullptr;
    _weathers[AWeather::E_WEATHER::SNOW] = new SnowWeather(_particleSystem, driver);
    _weathers[AWeather::E_WEATHER::RAIN] = new RainWeather(_particleSystem, driver);

    // Define the weather update speed (in ms)
    _updateSpeed = WEATHER_UPDATE_SPEED * 1000;
    // Init the time for the nex weather update
    _nextUpdate = _timer->getTime() + _updateSpeed;
    return 0;
}

int ParticleModule::update()
{
    // Manage weather update depending on the _updateSpeed
    if (_timer->getTime() > _nextUpdate)
    {
        auto weather = _weathers[_weather];
        if (weather)
            weather->update(_particleSystem);
        _nextUpdate += _updateSpeed;
    }
    return 0;
}

void ParticleModule::setWeather(int w)
{
    _nextUpdate = _timer->getTime() + _updateSpeed;

    _weather = static_cast<AWeather::E_WEATHER>(w);
    auto weather = _weathers[_weather];
    if (weather)
        weather->setWeather(_particleSystem);
    else
        _particleSystem->setEmitter(nullptr);
}


ParticleModule::~ParticleModule()
{
    for (auto & weather : _weathers)
    {
        delete weather.second;
    }
    _weathers.clear();
}
