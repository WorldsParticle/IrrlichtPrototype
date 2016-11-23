#pragma once

#include <irrlicht.h>
#include "gui_radiocheckboxgroup.h"
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
		irr::gui::CGUIRadioCheckBoxGroup*	envRadioBox;
		irr::gui::CGUIRadioCheckBoxGroup*	timeRadioBox;
		irr::gui::CGUIRadioCheckBoxGroup*	climatRadioBox;
		irr::gui::IGUIEnvironment*		env;
	};
	// Define some values that we'll use to identify individual GUI controls.
	enum
	{
		GUI_ID_GENERATE_BUTTON = 101,
		GUI_ID_APPLY_PARAMS_BUTTON,
		GUI_ID_MUSIC_SCROLL_BAR,
		GUI_ID_SOUND_SCROLL_BAR,
		GUI_ID_QUIT,
		GUI_ID_BACK
	};

	MyEventReceiver(Core *core, SAppContext & context);

	bool OnEvent(const irr::SEvent& event);

	void switchCameraMode();
	void switchWireframe();

private:

	Core	    *_core;
	SAppContext _context;
	irr::gui::IGUIWindow *confirmQuit = nullptr;

public://Called by the core at initialization
	void ApplyGUIParametersToWorld();
	void Generate();
};
