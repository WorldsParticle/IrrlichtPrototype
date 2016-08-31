#include "MyEventReceiver.h"
#include "Core.h"

using namespace irr;

MyEventReceiver::MyEventReceiver(Core *core)
	: _core(core)
{
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
	// check if user presses the key 'W' or 'D'
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
	{
		switch (event.KeyInput.Key)
		{
		case irr::KEY_KEY_N: // night
			_core->skyboxModule->activeNight(true);
			return true;
		case irr::KEY_KEY_B: // day
			_core->skyboxModule->activeNight(false);
			return true;
        case irr::KEY_KEY_P: // change weather
            _core->particleModule->activate();
            return true;
		case irr::KEY_ESCAPE: // quit
			_core->close();
			return true;
		default:
			break;
		}
	}

	return false;
}