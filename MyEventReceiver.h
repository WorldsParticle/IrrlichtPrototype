#pragma once

#include <irrlicht.h>

class Core;

class MyEventReceiver : public irr::IEventReceiver
{
public:

	MyEventReceiver(Core *core);

	bool OnEvent(const irr::SEvent& event);

private:
	Core *_core;
};
