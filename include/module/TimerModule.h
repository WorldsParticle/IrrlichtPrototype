#pragma once

#include "module/AModule.h"

class TimerModule : public AModule
{
public:
    TimerModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera)
        : AModule{c, _device, _camera },
        _timer(nullptr),
        _lastTime(0),
        _elapsedTime(0)
    {}

public:
    virtual int init();
    virtual int update();

    void        setTime(irr::u32 time);
    float       getElapsedTime() const;
    irr::u32    getTime() const;

private:
    irr::ITimer * _timer;
    irr::u32      _lastTime;
    float         _elapsedTime;
};