#include "scene/weather/SnowWeather.h"
#include "Configuration.h"

SnowWeather::SnowWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                         irr::video::IVideoDriver * driver)
{
    // Create new BoxEmiter
    _emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-1000, -1000, -1000, 1000, 1000, 1000),   // Coordinates
        irr::core::vector3df(0.0f, -0.08f, 0.0f),                               // Direction
        200, 500,                                                               // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        6000, 7000,                                                             // Min/Max LifeTime
        20,                                                                     // Angle deviation
        irr::core::dimension2df(5.0f, 5.0f),                                    // Size min
        irr::core::dimension2df(15.0f, 15.0f));                                 // Size max

    _texture = driver->getTexture(RESOURCES_PATH "/snow.bmp"); 
}

void SnowWeather::updateWeather()
{
    switch (_intensity)
    {
    case WeatherIntensity::LOW:
        updateEmitter(200, 500, irr::core::vector3df(0.0f, -0.08f, 0.0f));
        break;
    case WeatherIntensity::MEDIUM:
        updateEmitter(500, 800, irr::core::vector3df(0.0f, -0.1f, 0.0f));
        break;
    case WeatherIntensity::HIGH:
        updateEmitter(800, 1300, irr::core::vector3df(0.0f, -0.15f, 0.0f));
        break;
    }
}