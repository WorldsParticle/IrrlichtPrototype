#pragma once

#include "AModule.h"

class ParticleModule : public AModule
{
public:
    ParticleModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule{ _device, _camera }
    {}

public:
    virtual int init();
    virtual int update();
};