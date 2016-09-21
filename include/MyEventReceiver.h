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
