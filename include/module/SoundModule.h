#pragma once

#include "AModule.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"

const float DISTANCEFACTOR = 100.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.

//Manages the sound lib, listener, and background music
class SoundModule : public AModule
{
public:
    SoundModule(Core *c, IrrlichtDevice* _device,
    scene::ICameraSceneNode* _camera)
    : AModule(c, _device, _camera)
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
    void setListenerPos(int, int, int);
    //Adds a background music
    void AddBGMusic(std::string);
    //Changes the volume. 1.0 is default, >1 is louder, < 0 "inverts the signal"
    void SetVolume (float);
    //Changes background music according to environment, time, and weather. Used when generating a new scene.
    void SetEnvironmentalSound(int, int, int);
public:
    FMOD::System	*soundSystem;

private:
    float		_volume = 1.0f;
    FMOD_VECTOR		_listenerPos;

    FMOD::Sound		*_BGSound;
    FMOD::Channel	*_BGChannel;
};
