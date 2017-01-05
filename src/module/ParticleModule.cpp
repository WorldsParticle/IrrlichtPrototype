#include "module/ParticleModule.h"
#include "scene/weather/SnowWeather.h"
#include "scene/weather/RainWeather.h"
#include "scene/weather/HailWeather.h"

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
    _weathers[AWeather::E_WEATHER::HAIL] = new HailWeather(_particleSystem, driver);

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
        if (_IGWeathers[_IGWeather] == AWeather::E_WEATHER::NONE)
            updateWeather();
        else
        {
            updateIntensity();
            updateWeather();
        }

        _nextUpdate += _updateSpeed;
    }
    return 0;
}

void ParticleModule::updateWeather()
{
    // 20% chance to change Weather
    int random = rand() % 10;
    int threshold = 2;
    if (random < threshold)
    {
        // 50/50 chance to have next or previous weather
        random < threshold / 2 ?
            previousWeather() :
            nextWeather();

    }
}

void ParticleModule::updateIntensity()
{
    // 50% chance to Increase or Decrease Intensity
    int random = rand() % 10;
    if (random < 5)
        decreaseIntensity();
    else
        increaseIntensity();

    // Update weather particles with new intensity
    int w = _IGWeathers[_IGWeather];
    AWeather * weather = _weathers[w];

    if (weather)
        weather->update(_weatherIntensity);
    else
        _particleSystem->setEmitter(nullptr);
}

#include <iostream>
void ParticleModule::setWeather(int w, int intensity) // Get vector<int> w
{
    // Define time for next weather update
    _nextUpdate = _timer->getTime() + _updateSpeed;

    // For now but will get it from param
    std::vector<int> ws = { w };
    _IGWeathers = ws;
    _weatherIntensity = static_cast<AWeather::E_INTENSITY>(intensity);

    std::cout << "inten:" << intensity << " / "<< "w: " << w << "\n";

    // Start with a random weather
    int random = rand() % ws.size();
    std::cout <<  "YO:m" << std::endl;
    _IGWeather = 0;
    std::cout <<  "YO:mqsdsq" << std::endl;
    // Update Particles with new weather
    changeWeather();

    // FOG but need to set the material flag EMF_FOG_ENABLe to true in every scene node
  /*  driver->setFog(video::SColor(255, 255, 255, 255),
                   video::EFT_FOG_LINEAR,
                   250, 1000,
                   .05f,
                   false, false);*/
}

void ParticleModule::changeWeather()
{
    int w = _IGWeathers[_IGWeather];
    AWeather * weather = _weathers[w];

    std::cout << "W: " << w <<"\n";
    if (weather)
        weather->setWeather(_particleSystem, _weatherIntensity);
    else
        _particleSystem->setEmitter(nullptr);
}


void ParticleModule::decreaseIntensity()
{
    switch (_weatherIntensity)
    {
    case AWeather::E_INTENSITY::MEDIUM:
        _weatherIntensity = AWeather::E_INTENSITY::LOW;
        break;
    case AWeather::E_INTENSITY::HIGH:
        _weatherIntensity = AWeather::E_INTENSITY::MEDIUM;
        break;
    }
}

void ParticleModule::increaseIntensity()
{
    switch (_weatherIntensity)
    {
    case AWeather::E_INTENSITY::LOW:
        _weatherIntensity = AWeather::E_INTENSITY::MEDIUM;
        break;
    case AWeather::E_INTENSITY::MEDIUM:
        _weatherIntensity = AWeather::E_INTENSITY::HIGH;
        break;
    }
}


void ParticleModule::previousWeather()
{
    if (_IGWeather == 0)
        return;

    _IGWeather--;
    // We don't want no weather if intensity is not LOW
    if (_IGWeathers[_IGWeather] == AWeather::E_WEATHER::NONE)
        _weatherIntensity == AWeather::E_INTENSITY::LOW ?
        _weatherIntensity = AWeather::E_INTENSITY::ZERO : _IGWeather++;

    changeWeather();
}

void ParticleModule::nextWeather()
{
    if (_IGWeather == _IGWeathers.size() - 1)
        return;

    if (_IGWeathers[_IGWeather] == AWeather::E_WEATHER::NONE)
        _weatherIntensity = AWeather::E_INTENSITY::LOW;
    _IGWeather++;

    changeWeather();
}


ParticleModule::~ParticleModule()
{
    for (auto & weather : _weathers)
    {
        delete weather.second;
    }
    _weathers.clear();
}
