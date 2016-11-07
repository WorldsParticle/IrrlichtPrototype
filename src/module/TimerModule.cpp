#include "module/TimerModule.h"

int TimerModule::init()
{
    _timer = device->getTimer();
    _timer->setTime(0);

    return 0;
}

int TimerModule::update()
{
    irr::u32 time = _timer->getTime();
    _elapsedTime = (time - _lastTime) / 1000.0f;
    _lastTime = time;

    return 0;
}


void TimerModule::setTime(irr::u32 time)
{
    _timer->setTime(time);
    _lastTime = time;
    _elapsedTime = 0;
}

irr::u32 TimerModule::getTime() const
{
    irr::u32 time = _timer->getTime();
    return time;
}

float TimerModule::getElapsedTime() const
{
    return _elapsedTime;
}