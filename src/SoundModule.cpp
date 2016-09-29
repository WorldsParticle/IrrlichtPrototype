//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) WorldsParticle
//

#include <iostream>

#include "SoundModule.h"

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

void SoundModule::setListenerPos(float x, float y, float z)
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
