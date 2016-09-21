//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) WorldsParticle
//

#include "MyEventReceiver.h"
#include "Core.h"
#include "SkyboxModule.h"
#include "ParticleModule.h"
#include "TerrainModule.h"
#include <iostream>

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
			_core->getSkyboxModule()->activeNight(true);
			return true;
		case irr::KEY_KEY_B: // day
			_core->getSkyboxModule()->activeNight(false);
			return true;
        case irr::KEY_KEY_P: // change weather
            _core->getParticleModule()->activate();
            return true;
		case irr::KEY_ESCAPE: // quit
            _core->getIrrlichtDevice()->closeDevice();
            return true;
		case irr::KEY_KEY_I: // interface
			if (_core->isInterfaceActive() == false)
			{
			    _core->getIrrlichtDevice()->getCursorControl()->setVisible(true);
			    _core->getActiveCamera()->setInputReceiverEnabled(false);
                _core->setInterfaceActive(true);
			}
			else
			{
			    _core->getIrrlichtDevice()->getCursorControl()->setVisible(false);
			    _core->getActiveCamera()->setInputReceiverEnabled(true);
                _core->setInterfaceActive(false);
            }
			return true;
        case irr::KEY_KEY_G:
            _core->getTerrainModule()->generate(513, rand());
            _core->getTerrainModule()->setHeightmap();
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
						//std::cout << "Environment: " << _context.envRadioBox->getSelected() << std::endl;
						//std::cout << "Time: " << _context.timeRadioBox->getSelected() << std::endl;
						//std::cout << "Climat: " << _context.climatRadioBox->getSelected() << std::endl;
						//generatorModule->buildTerrain(_context.envRadioBox->getSelected());
						//_context.device->closeDevice();
						return true;

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
