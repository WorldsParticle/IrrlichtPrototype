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
    _elapsedTime = (time - _lastTime);
    _lastTime = time;

    // Update InGame Time
    _IGTime += _elapsedTime;

    return 0;
}


void TimerModule::setTime(irr::u32 time)
{
    // Set IGTime in ms depending on defined time (0 to 24h) and TIME_OF_DAY duration
    _IGTime = time * TIME_OF_DAY / 24;
    // Increase IGTime by NIGHT_START to get a proper midnight
    _IGTime += TIME_OF_DAY * 0.575f;
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