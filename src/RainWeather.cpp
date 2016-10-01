#include "RainWeather.h"
#include "Configuration.h"

RainWeather::RainWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                         irr::video::IVideoDriver * driver)
{
    // Create new BoxEmiter
    _emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5000, 1200, -5000, 5000, 1200, 5000),    // Coordinates
        irr::core::vector3df(0.0f, -1.0f, 0.0f),                                // Direction
        5000, 5200,                                                             // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        1200, 1500,                                                             // Min/Max LifeTime
        5,                                                                      // Angle deviation
        irr::core::dimension2df(5.0f, 5.0f),                                  // Size min
        irr::core::dimension2df(10.0f, 10.0f));                                 // Size max

    _texture = driver->getTexture(RESOURCES_PATH "/one_drop.png");
}
