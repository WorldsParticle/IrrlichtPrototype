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
#include "GUIModule.h"

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
			if (_core->getGUIModule()->isVisible() == false)
			{
			    _core->getIrrlichtDevice()->getCursorControl()->setVisible(true);
			    _core->getActiveCamera()->setInputReceiverEnabled(false);
                _core->getGUIModule()->setVisible(true);
			}
			else
			{
			    _core->getIrrlichtDevice()->getCursorControl()->setVisible(false);
			    _core->getActiveCamera()->setInputReceiverEnabled(true);
                _core->getGUIModule()->setVisible(false);
            }
			return true;
		default:
			break;
		}
	}
	//if (event.EventType == EET_GUI_EVENT)
	//{
	//	s32 id = event.GUIEvent.Caller->getID();
	//	IGUIEnvironment* env = _context.device->getGUIEnvironment();

	//	switch(event.GUIEvent.EventType)
	//	{
	//		case EGET_BUTTON_CLICKED:
	//			switch(id)
	//			{
	//				case GUI_ID_QUIT_BUTTON:
	//					_context.device->closeDevice();
	//					return true;

	//				case GUI_ID_FILE_OPEN_BUTTON:
	//					_context.listbox->addItem(L"File open");
	//					// There are some options for the file open dialog
	//					// We set the title, make it a modal window, and make sure
	//					// that the working directory is restored after the dialog
	//					// is finished.
	//					env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
	//					return true;

	//				default:
	//					return false;
	//			}
	//			break;

	//		case EGET_FILE_SELECTED:
	//			{
	//				// show the model filename, selected in the file dialog
	//				IGUIFileOpenDialog* dialog =
	//					(IGUIFileOpenDialog*)event.GUIEvent.Caller;
	//				_context.listbox->addItem(dialog->getFileName());
	//			}
	//			break;

	//		default:
	//			break;
	//	}
	//}

	return false;
}
