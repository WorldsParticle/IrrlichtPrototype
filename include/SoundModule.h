#pragma once

#include "AModule.h"
#include "fmod.hpp"
#include "fmod_errors.h"

const float DISTANCEFACTOR = 100.0f;          // Units per meter.  I.e feet would = 3.28.  centimeters would = 100.

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
    virtual int init();
    virtual int update();
    int FMODErrorCheck(int);
    void setListenerPos(int, int, int);
    void AddBGMusic(std::string);

public:
    FMOD::System	*soundSystem;

private:
    FMOD_VECTOR		_listenerPos;

    FMOD::Sound		*_BGSound;
    FMOD::Channel	*_BGChannel;
};

