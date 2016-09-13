#pragma once

#include <irrlicht.h>
#include "driverChoice.h"

using namespace irr;

class Core;

class MyEventReceiver : public irr::IEventReceiver
{
public:

	// Declare a structure to hold some context for the event receiver so that it
	// has it available inside its OnEvent() method.
	struct SAppContext
	{
		irr::IrrlichtDevice	*device;
		irr::s32		counter;
		irr::gui::IGUIListBox*	listbox;
	};
	// Define some values that we'll use to identify individual GUI controls.
	enum
	{
		GUI_ID_QUIT_BUTTON = 101,
		//GUI_ID_NEW_WINDOW_BUTTON,
		GUI_ID_FILE_OPEN_BUTTON
		//GUI_ID_TRANSPARENCY_SCROLL_BAR
	};

	MyEventReceiver(Core *core, SAppContext & context);

	bool OnEvent(const irr::SEvent& event);

private:

	Core	    *_core;
	SAppContext _context;
};
