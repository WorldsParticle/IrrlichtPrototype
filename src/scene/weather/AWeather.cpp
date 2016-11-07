#include "scene/weather/AWeather.h"

void AWeather::update(irr::scene::IParticleSystemSceneNode * ps)
{
    // Define threshold for weather changing
    int threshold;
    _intensity == AWeather::WeatherIntensity::ZERO ||
        _intensity == AWeather::WeatherIntensity::LOW ?
        threshold = 2 : threshold = 5;

    // Increase/Decrease intensity depending on the threshold
    int random = rand() % 10;
    if (random < threshold)
        decreaseIntensity(ps);
    else
        increaseIntensity(ps);

    // Update weather particles with new intensity
    updateWeather();
}

void AWeather::updateEmitter(int minPart, int maxPart, irr::core::vector3df direction)
{
    _emitter->setMinParticlesPerSecond(minPart);
    _emitter->setMaxParticlesPerSecond(maxPart);
    _emitter->setDirection(direction);
}


void AWeather::increaseIntensity(irr::scene::IParticleSystemSceneNode * ps)
{
    switch (_intensity)
    {
    case WeatherIntensity::ZERO:
        _intensity = WeatherIntensity::LOW;
        ps->setEmitter(_emitter);   // Reset emitter to emit particles again
        break;
    case WeatherIntensity::LOW:
        _intensity = WeatherIntensity::MEDIUM;
        break;
    case WeatherIntensity::MEDIUM:
        _intensity = WeatherIntensity::HIGH;
        break;
    }
}

void AWeather::decreaseIntensity(irr::scene::IParticleSystemSceneNode * ps)
{
    switch (_intensity)
    {
    case WeatherIntensity::LOW:
        _intensity = WeatherIntensity::ZERO;
        ps->setEmitter(nullptr);    // Stop emitting particles
        break;
    case WeatherIntensity::MEDIUM:
        _intensity = WeatherIntensity::LOW;
        break;
    case WeatherIntensity::HIGH:
        _intensity = WeatherIntensity::MEDIUM;
        break;
    }
}


void AWeather::setWeather(irr::scene::IParticleSystemSceneNode * ps)
{
    ps->setEmitter(_emitter);
    ps->setMaterialTexture(0, _texture);
    _intensity = WeatherIntensity::LOW;
    updateWeather();
}