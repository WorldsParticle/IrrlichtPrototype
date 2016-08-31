//
// Created by neige on 23/08/16.
//

#include "SoundModule.h"

//TODO: better error checking
int SoundModule::init()
{
    FMOD_RESULT			result;
    unsigned int		version;

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

    _BGChannel = NULL;
    _BGSound = NULL;
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
    if (_BGChannel != NULL) {
        _BGChannel->set3DAttributes(&listenerNewPos, NULL);
    }
}

void SoundModule::AddBGMusic(std::string path) {
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
