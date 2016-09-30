#include "MyEventReceiver.h"
#include "Core.h"
#include "SkyboxModule.h"
#include "ParticleModule.h"
#include "TerrainModule.h"
#include <iostream>

using namespace irr;

MyEventReceiver::MyEventReceiver(Core *core, SAppContext & context)
	: _core(core), _context(context)
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
			if (confirmQuit == nullptr) {
				if (!_core->isInterfaceVisible())
					_core->toggleInterface();
				confirmQuit = _context.env->addWindow(
						rect<s32>(100, 100, 250, 200),
							false, // modal?
							L"Confirm quit");

						_context.env->addStaticText(L"Do you want to quit ?",
							rect<s32>(10,35,170,50),
							false, // border?
							true, // wordwrap?
							confirmQuit);
						_context.env->addButton(rect<s32>(30, 60, 60, 80), confirmQuit, MyEventReceiver::GUI_ID_QUIT, L"Yes", L"Quit");
						_context.env->addButton(rect<s32>(70, 60, 100, 80), confirmQuit, MyEventReceiver::GUI_ID_BACK, L"No", L"Cancel");
			} else {
			    confirmQuit->remove();
			    confirmQuit = nullptr;
			}
			return true;
		case irr::KEY_KEY_I: // interface
			_core->toggleInterface();
			return true;
        case irr::KEY_KEY_G:
            _core->terrainModule->generate(513, rand());
            _core->terrainModule->setHeightmap();
            return true;
		default:
			break;
		}
	}
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
					case GUI_ID_GENERATE_BUTTON:
						std::cout << "Environment: " << _context.envRadioBox->getSelected() << std::endl;
						std::cout << "Time: " << _context.timeRadioBox->getSelected() << std::endl;
						std::cout << "Climat: " << _context.climatRadioBox->getSelected() << std::endl;
						//generatorModule->buildTerrain(_context.envRadioBox->getSelected());
						//_context.device->closeDevice();
						return true;

					case GUI_ID_QUIT:
						_core->close();

					case GUI_ID_BACK:
						confirmQuit->remove();
						confirmQuit = nullptr;

					default:
						return false;
				}
				break;

			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_MUSIC_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					std::cout << "Music volume: " << pos << std::endl;
				}
				else if (id == GUI_ID_SOUND_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					std::cout << "Sound volume: " << pos << std::endl;
				}
				break;

			default:
				break;
		}
	}

	return false;
}
