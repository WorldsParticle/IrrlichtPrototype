#include "scene/weather/AWeather.h"


void AWeather::updateEmitter(int minPart, int maxPart, irr::core::vector3df direction)
{
    _emitter->setMinParticlesPerSecond(minPart);
    _emitter->setMaxParticlesPerSecond(maxPart);
    _emitter->setDirection(direction);
}


void AWeather::setWeather(irr::scene::IParticleSystemSceneNode * ps, E_INTENSITY intensity)
{
    ps->setEmitter(_emitter);
    ps->setMaterialTexture(0, _texture);
    update(intensity);
}
