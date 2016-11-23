#include "module/TimerModule.h"
#include "irrlicht/CTimer.h"

int TimerModule::init()
{
    _timer = device->getTimer();
    setTime(0);

    return 0;
}

int TimerModule::update()
{
    // Calc elapsedTime
    irr::u32 time = _timer->getTime();
    _elapsedTime = (time - _lastTime) / 1000.0f;
    _lastTime = time;

    // Update InGame Time
    _IGTime += _elapsedTime;

    return 0;
}


void TimerModule::setTime(irr::u32 time)
{
    _IGTime = time;
    _elapsedTime = 0;
}

irr::u32 TimerModule::getTime() const
{
    return _IGTime;
}

float TimerModule::getElapsedTime() const
{
    return _elapsedTime;
}