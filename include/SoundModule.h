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

#pragma once

#include "AModule.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

const float DISTANCEFACTOR = 100.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.

//Manages the sound lib, listener, and background music
class SoundModule : public AModule
{
public:
    SoundModule(IrrlichtDevice* _device,
    scene::ICameraSceneNode* _camera)
    : AModule(_device, _camera)
    {
    }
    ~SoundModule()
    {
    }
    //Initializes FMOD and listener position
    virtual int init();
    //Updates sound system once per frame
    virtual int update();
    //FMOD Error checks
    int FMODErrorCheck(int);
    //Sets the listener position
    void setListenerPos(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    //Adds a background music
    void AddBGMusic(std::string);

public:
    FMOD::System	*soundSystem;

private:
    FMOD_VECTOR		_listenerPos;

    FMOD::Sound		*_BGSound;
    FMOD::Channel	*_BGChannel;
};

