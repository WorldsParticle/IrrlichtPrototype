#include "scene/weather/RainWeather.h"
#include "Configuration.h"

RainWeather::RainWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                         irr::video::IVideoDriver * driver)
{
    // Create new BoxEmiter
    _emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-1000, -1000, -1000, 1000, 1000, 1000),   // Coordinates
        irr::core::vector3df(0.0f, -0.7f, 0.0f),                                // Direction
        1000, 2000,                                                             // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        800, 1000,                                                              // Min/Max LifeTime
        10,                                                                     // Angle deviation
        irr::core::dimension2df(5.0f, 5.0f),                                    // Size min
        irr::core::dimension2df(8.0f, 8.0f));                                   // Size max

    _texture = driver->getTexture(RESOURCES_PATH "/one_drop.png");
}

void RainWeather::update(E_INTENSITY intensity)
{
    switch (intensity)
    {
    case E_INTENSITY::LOW:
        updateEmitter(1000, 2000, irr::core::vector3df(0.0f, -0.7f, 0.0f));
        break;
    case E_INTENSITY::MEDIUM:
        updateEmitter(2000, 5000, irr::core::vector3df(0.0f, -0.75f, 0.0f));
        break;
    case E_INTENSITY::HIGH:
        updateEmitter(5000, 8000, irr::core::vector3df(0.0f, -0.77f, 0.0f));
        break;
    }
}