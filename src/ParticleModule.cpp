#include "ParticleModule.h"

int ParticleModule::init()
{
    // Create new ParticleSystem and disable the default Emiter
    irr::scene::IParticleSystemSceneNode * particleSystem = smgr->addParticleSystemSceneNode(false);
    particleSystem->setPosition(camera->getPosition());

    // Create new BoxEmiter
    irr::scene::IParticleEmitter * emitter = particleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-5000, 1200, -5000, 5000, 1200, 5000),    // Coordinates
        irr::core::vector3df(0.0f, -0.15f, 0.0f),                                // Direction
        1000, 1200,                                                             // Min/Max Particles emission
        irr::video::SColor(255, 255, 255, 255),
        irr::video::SColor(255, 255, 255, 255),
        15000, 20000,                                                           // Min/Max LifeTime
        20,                                                                     // Angle deviation
        irr::core::dimension2df(5.0f, 5.0f),                                    // Size min
        irr::core::dimension2df(15.0f, 15.0f));                                 // Size max

    // Attach the emitter to the ParticleSystem
    particleSystem->setEmitter(emitter);
    // Set the Material and options
    particleSystem->setMaterialTexture(0, driver->getTexture("./ressources/snow.bmp"));
    particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    particleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    particleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

    emitter->drop();

    return 0;
}

int ParticleModule::update()
{
    // Nothing to do
    return 0;
}