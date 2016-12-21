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


void ParticleModule::setWeather(int w) // Get vector<int> w
{
    // Define time for next weather update
    _nextUpdate = _timer->getTime() + _updateSpeed;

    // For now but will get it from param
    std::vector<int> ws = { w, AWeather::E_WEATHER::RAIN };
    _IGWeathers = ws;
    _weatherIntensity = AWeather::E_INTENSITY::LOW;

    // Start with a random weather
    int random = rand() % ws.size();
    _IGWeather = ws[random];

    // Update Particles with new weather
    changeWeather();
}

void ParticleModule::changeWeather()
{
    int w = _IGWeathers[_IGWeather];
    AWeather * weather = _weathers[w];

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
