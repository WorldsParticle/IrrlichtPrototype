//
// Created by neige on 23/08/16.
//

#include "SoundModule.h"

//TODO: better error checking
int SoundModule::init()
{
    FMOD_RESULT			result;
    unsigned int		version;
    int					nbDrivers;
    FMOD_SPEAKERMODE	speakerMode;
    char 				name[256];


    result = FMOD::System_Create(&soundSystem);
    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR: " << result << std::endl;
        return 1;
    }
    soundSystem->getVersion(&version);
    if (version < FMOD_VERSION) {
        std::cout << "FMOD ERROR: Using an old version of FMOD" << std::endl;
        return 1;
    }
    result = soundSystem->init(100, FMOD_INIT_NORMAL, NULL);
    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR: " << result << std::endl;
        return 1;
    }
    result = soundSystem->set3DSettings(1.0, DISTANCEFACTOR, 1.0f);
    FMODErrorCheck(result);

    //set listener position
    listenerpos = {camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z};
    FMOD_VECTOR forward        = { 0.0f, 0.0f, 1.0f };
    FMOD_VECTOR up             = { 0.0f, 1.0f, 0.0f };
    result = soundSystem->set3DListenerAttributes(0, &listenerpos, NULL, &forward, &up);
    FMODErrorCheck(result);


    /*
    //create test sound
    result = soundSystem->createSound("ressources/drumloop.wav", FMOD_3D, 0, &soundTest);
    FMODErrorCheck(result);
    result = soundTest->set3DMinMaxDistance(5.0f * DISTANCEFACTOR, 500.0f * DISTANCEFACTOR);
    FMODErrorCheck(result);
    result = soundTest->setMode(FMOD_LOOP_NORMAL);
    FMODErrorCheck(result);

    //play test sound
    channelTest = 0;
    FMOD_VECTOR pos = {camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z};
    FMOD_VECTOR vel = {0.0f, 0.0f, 0.0f};
    result = soundSystem->playSound(soundTest, 0, true, &channelTest);
    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR: " << result << std::endl;
        return 1;
    }
    result = channelTest->set3DAttributes(&pos, &vel);
    FMODErrorCheck(result);
    result = channelTest->setPaused(false);
    FMODErrorCheck(result);
    */
     return 0;
}

int SoundModule::update() {
    setListenerPos(camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z);
    soundSystem->update();
    return 0;
}

int SoundModule::FMODErrorCheck(int result) {

    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR: " << result << std::endl;
        return 1;
    }
    return 0;
}

void SoundModule::setListenerPos(int x = 0, int y = 0, int z = 0)
{
    FMOD_VECTOR listenerNewPos = {x, y, z};
    listenerpos = listenerNewPos;
    soundSystem->set3DListenerAttributes(0, &listenerpos, NULL, NULL, NULL);
}
