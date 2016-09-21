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

