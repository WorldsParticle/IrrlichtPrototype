#include "ParticleModule.h"
#include "SnowWeather.h"
#include "RainWeather.h"

int ParticleModule::init()
{
    // Create new ParticleSystem and disable the default Emiter
    _particleSystem = smgr->addParticleSystemSceneNode(false);
    _particleSystem->setPosition(camera->getPosition());

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

    return 0;
}

int ParticleModule::update()
{
    // Nothing to do
    return 0;
}

void ParticleModule::setWeather(int w)
{
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
