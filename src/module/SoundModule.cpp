//
// Created by neige on 23/08/16.
//

#include <iostream>

#include "module/SoundModule.h"
#include "Configuration.h"

int SoundModule::init()
{
    FMOD_RESULT			result;
    unsigned int		version;

    result = FMOD::System_Create(&soundSystem);
    FMODErrorCheck(result);
    soundSystem->getVersion(&version);
    if (version < FMOD_VERSION)
    {
        std::cout << "FMOD ERROR: Using an old version of FMOD" << std::endl;
        return 1;
    }
    result = soundSystem->init(100, FMOD_INIT_NORMAL, NULL);
    FMODErrorCheck(result);
    result = soundSystem->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
    FMODErrorCheck(result);

    //set listener position
    _listenerPos = {camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z};
    FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
    result = soundSystem->set3DListenerAttributes(0, &_listenerPos, NULL, &forward, &up);
    FMODErrorCheck(result);

    _BGChannel = NULL;
    _BGSound = NULL;
     return 0;
}

int SoundModule::update()
{
    setListenerPos(camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z);
    soundSystem->update();
    return 0;
}

int SoundModule::FMODErrorCheck(int result)
{
    if (result != FMOD_OK)
    {
        std::cout << "FMOD ERROR: " << result << std::endl;
        return 1;
    }
    return 0;
}

void SoundModule::setListenerPos(float x = 0, float y = 0, float z = 0)
{
    FMOD_VECTOR listenerNewPos = {x, y, z};
    _listenerPos = listenerNewPos;
    soundSystem->set3DListenerAttributes(0, &_listenerPos, NULL, NULL, NULL);
    if (_BGChannel != NULL)
    {
        _BGChannel->set3DAttributes(&listenerNewPos, NULL);
    }
}

void SoundModule::AddBGMusic(std::string path)
{
    _BGSound->release();
    soundSystem->createSound(path.c_str(), FMOD_3D, 0, &_BGSound);
    _BGSound->set3DMinMaxDistance(5.0f * DISTANCEFACTOR, 500.0f * DISTANCEFACTOR);
    _BGSound->setMode(FMOD_LOOP_NORMAL);
    soundSystem->playSound(_BGSound, 0, true, &_BGChannel);

    FMOD_VECTOR pos;
    soundSystem->get3DListenerAttributes(0, &pos, NULL, NULL, NULL);
    _BGChannel->set3DAttributes(&pos, NULL);
    _BGChannel->set3DAttributes(&pos, NULL);
    _BGChannel->setPaused(false);
}

void SoundModule::SetEnvironmentalSound(int env, int time, int weather)
{
    /*
     * env: 0-mountain, 1-forest, 2-beach
     * time: 0-day, 1-night,
     * weather: 0-sun, 1-rain, 2-snow
     */
    if (weather == 0)   //sun
    {
        if (env == 0 && time == 0) //mountain/day
        {
            AddBGMusic(RESOURCES_PATH "/sound/mountain.mp3");
        }
        else if (env == 1 && time == 0) //forest/day
        {
            AddBGMusic(RESOURCES_PATH "/sound/forest.mp3");
        }
        else if ((env == 0 || env == 1) && time == 1) //mountain|forest/night
        {
            AddBGMusic(RESOURCES_PATH "/sound/cicadas.mp3");
        }
        else if (env == 2) //beach/day|night
        {
            AddBGMusic(RESOURCES_PATH "/sound/beach.mp3");
        }
    }
    else if (weather == 1)  //rain
    {
        AddBGMusic(RESOURCES_PATH "/sound/rain.mp3");
    }
    else  //snow
    {
        AddBGMusic(RESOURCES_PATH "/sound/wind.mp3");
    }
    _BGChannel->setVolume(_volume);
}

void SoundModule::SetVolume(float vol)
{
    _volume = vol;
    _BGChannel->setVolume(vol);
}
