#include "MyEventReceiver.h"
#include "Core.h"
#include "SkyboxModule.h"
#include "ParticleModule.h"

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
			_core->close();
			return true;
		case irr::KEY_KEY_I: // interface
			if (!_core->isInterfaceActive)
			{
			    _core->device->getCursorControl()->setVisible(true);
			    _core->camera->setInputReceiverEnabled(false);
			}
			else
			{
			    _core->device->getCursorControl()->setVisible(false);
			    _core->camera->setInputReceiverEnabled(true);
			}
			_core->isInterfaceActive = !_core->isInterfaceActive;
			return true;
		default:
			break;
		}
	}
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		IGUIEnvironment* env = _context.device->getGUIEnvironment();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
					case GUI_ID_QUIT_BUTTON:
						_context.device->closeDevice();
						return true;

					case GUI_ID_FILE_OPEN_BUTTON:
						_context.listbox->addItem(L"File open");
						// There are some options for the file open dialog
						// We set the title, make it a modal window, and make sure
						// that the working directory is restored after the dialog
						// is finished.
						env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
						return true;

					default:
						return false;
				}
				break;

			case EGET_FILE_SELECTED:
				{
					// show the model filename, selected in the file dialog
					IGUIFileOpenDialog* dialog =
						(IGUIFileOpenDialog*)event.GUIEvent.Caller;
					_context.listbox->addItem(dialog->getFileName());
				}
				break;

			default:
				break;
		}
	}

	return false;
}
