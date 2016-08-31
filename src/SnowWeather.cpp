#include "SnowWeather.h"

SnowWeather::SnowWeather(irr::scene::IParticleSystemSceneNode * particleSystem,
                         irr::video::IVideoDriver * driver) {
    // Create new BoxEmiter
    _emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5000, 1200, -5000, 5000, 1200, 5000),    // Coordinates
        irr::core::vector3df(0.0f, -0.15f, 0.0f),                               // Direction
        1000, 1200,                                                             // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        8000, 10000,                                                            // Min/Max LifeTime
        20,                                                                     // Angle deviation
        irr::core::dimension2df(5.0f, 5.0f),                                    // Size min
        irr::core::dimension2df(15.0f, 15.0f));                                 // Size max

    _texture = driver->getTexture("./ressources/snow.bmp");
}
