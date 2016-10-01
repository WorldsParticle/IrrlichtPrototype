#include "Core.h"
#include "MyEventReceiver.h"
#include "ElementsModule.h"
#include "SkyboxModule.h"
#include "TerrainModule.h"
#include "WaterModule.h"
#include "SoundModule.h"
#include "ParticleModule.h"
#include "gui_radiocheckboxgroup.h"

#include "Configuration.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int Core::initIrrlicht()
{
	// ask user for driver
	video::E_DRIVER_TYPE driverType = driverChoiceConsole();
	if (driverType == video::EDT_COUNT)
		return 1;

	// create device with full flexibility over creation parameters
	// you can add more parameters if desired, check irr::SIrrlichtCreationParameters
	irr::SIrrlichtCreationParameters params;
	params.DriverType = driverType;
	params.WindowSize = core::dimension2d<u32>(1280, 720);
	device = createDeviceEx(params);

	if (device == 0)
		return 1; // could not create selected driver.

	_driver = device->getVideoDriver();
	_smgr = device->getSceneManager();
	_env = device->getGUIEnvironment();

	return 0;
}

int Core::initModules()
{
	//
	// BASIC ENVIRONNEMENT
	//
	device->setWindowCaption(L"WorldsParticle prototype");

	_driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	//
	// CAMERA
	//
    SKeyMap keyMap[8];
    keyMap[0].Action = EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = KEY_UP;
    keyMap[1].Action = EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = KEY_KEY_W;

    keyMap[2].Action = EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = KEY_DOWN;
    keyMap[3].Action = EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = KEY_KEY_S;

    keyMap[4].Action = EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = KEY_LEFT;
    keyMap[5].Action = EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = KEY_KEY_A;

    keyMap[6].Action = EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = KEY_RIGHT;
    keyMap[7].Action = EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = KEY_KEY_D;

	camera = _smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f, -1, keyMap, 8);
	//_smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	camera->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));
	camera->setTarget(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));
    camera->setFarValue(420000.0f);
	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	//
	//MODULES
	//
	//Add light
	_smgr->setAmbientLight(video::SColorf(0.6,0.6,0.6,1));

	soundModule = new SoundModule(device, camera);
	soundModule->init();
	soundModule->AddBGMusic(RESOURCES_PATH "/sound/river_bg.ogg");
	elementsModule = new ElementsModule(device, camera, soundModule->soundSystem);
	elementsModule->init();
	skyboxModule = new SkyboxModule(device, camera);
	skyboxModule->init();
	terrainModule = new TerrainModule(device, camera);
	terrainModule->init();
    camera->setPosition(core::vector3df(0.0, terrainModule->getHeight(0.0, 0.0), 0.0));
	waterModule = new WaterModule(device, camera, terrainModule);
	waterModule->init();
	particleModule = new ParticleModule(device, camera);
	particleModule->init();

	setGUI();

	return 0;
}

int Core::run()
{
	int lastFPS = -1;

	camera->setPosition(core::vector3df(2700, 255 * 2, 2600));

	while (device->run())
		if (device->isWindowActive())
		{
			elementsModule->update();
			skyboxModule->update();
			terrainModule->update();
			particleModule->update();
			soundModule->update();
			waterModule->update();

			_driver->beginScene(true, true, 0);

			_smgr->drawAll();
			_env->drawAll();

			_driver->endScene();

			// display frames per second in window title
			int fps = _driver->getFPS();
			if (lastFPS != fps)
			{
				core::stringw str = L"WorldsParticle prototype [";
				str += _driver->getName();
				str += "] FPS:";
				str += fps;
				// Also print terrain height of current camera position
				// We can use camera position because terrain is located at coordinate origin
				//str += " Height: ";
				//str += terrain->getHeight(camera->getAbsolutePosition().X,
				//		camera->getAbsolutePosition().Z);

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
		}
	return 0;
}

void Core::close()
{
	device->closeDevice();
}

void Core::setGUI()
{
	//set transparency of everyting in the interface to not transparent at all
	int alpha = 255;
	irr::gui::IGUISkin * skin = _env->getSkin();
	for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = skin->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(alpha);
		skin->setColor((EGUI_DEFAULT_COLOR)i, col);
	}

	//set other font
	skin->setFont(_env->getFont(RESOURCES_PATH "/fontlucida.png"));

	// add some help text
	_env->addStaticText( L"Press 'I' to toggle interface", core::rect<s32>(10, 10, 250, 30), false, true, 0, -1, true);

	//set background color
	_tab = _env->addTab(core::rect<s32>(0, 0, 400, 720));
	_tab->setDrawBackground(true);
	_tab->setBackgroundColor(SColor(255, 140, 140, 140));

	//add WorldsParticle logo
	_env->addImage(_driver->getTexture(RESOURCES_PATH "2017_logo_worldsparticle.png"), core::position2d<s32>(10, 10), true, _tab);

	int height = 20; //height of radiobuttons
	int width = 100; // width of radiobuttons with their text

	//create enivronment radioButtons
	CGUIRadioCheckBoxGroup *envRB = new CGUIRadioCheckBoxGroup(_env, _tab);
	IGUICheckBox* mountain = _env->addCheckBox(false, core::rect<s32>(0, 0, width, height), _tab, 0, L"Mountain");
	IGUICheckBox* forest = _env->addCheckBox(false, core::rect<s32>(width, 0, 2 * width, height), _tab, 0, L"Forest");
	IGUICheckBox* beach = _env->addCheckBox(false, core::rect<s32>(2 * width, 0, 3 * width, height), _tab, 0, L"Beach");
	int x = 50;
	int y = 50;
	envRB->add(mountain);
	envRB->add(forest);
	envRB->add(beach);

	//create time radioButtons
	CGUIRadioCheckBoxGroup *timeRB = new CGUIRadioCheckBoxGroup(_env, _tab);
	IGUICheckBox* day = _env->addCheckBox(false, core::rect<s32>(0, 0, width, height), _tab, 0, L"Day");
	IGUICheckBox* night = _env->addCheckBox(false, core::rect<s32>(width, 0, 2 * width, height), _tab, 0, L"Night");
	timeRB->add(day);
	timeRB->add(night);

	//create climat radioButtons
	CGUIRadioCheckBoxGroup *climatRB = new CGUIRadioCheckBoxGroup(_env, _tab);
	IGUICheckBox* sun = _env->addCheckBox(false, core::rect<s32>(0, 0, width, height), _tab, 0, L"Sun");
	IGUICheckBox* rain = _env->addCheckBox(false, core::rect<s32>(width, 0, 2 * width, height), _tab, 0, L"Rain");
	IGUICheckBox* snow = _env->addCheckBox(false, core::rect<s32>(2 * width, 0, 3 * width, height), _tab, 0, L"Snow");
	climatRB->add(sun);
	climatRB->add(rain);
	climatRB->add(snow);

	//position of radiobuttons
	envRB->setRelativePosition(core::rect<s32>(x, y, x + width * 3, y + height));
	y += height + 10;
	timeRB->setRelativePosition(core::rect<s32>(x, y, x + width * 2, y + height));
	y += height + 10;
	climatRB->setRelativePosition(core::rect<s32>(x, y, x + width * 3, y + height));

	y += height + 10;
	y += height + 10;
	_env->addStaticText(L"Music volume", rect<s32>(x, y, x + 100, y + height), false, true, _tab);
	IGUIScrollBar* musicScrollbar = _env->addScrollBar(true, rect<s32>(x + 100, y, x + 300, y + height), _tab, MyEventReceiver::GUI_ID_MUSIC_SCROLL_BAR);
	musicScrollbar->setMax(100);
	musicScrollbar->setPos(100);
	//setSkinTransparency(musicScrollbar->getPos(), env->getSkin());

	y += height + 10;
	_env->addStaticText(L"Sound volume", rect<s32>(x, y, x + 100, y + height), false, true, _tab);
	IGUIScrollBar* soundScrollbar = _env->addScrollBar(true, rect<s32>(x + 100, y, x + 300, y + height), _tab, MyEventReceiver::GUI_ID_SOUND_SCROLL_BAR);
	soundScrollbar->setMax(100);
	soundScrollbar->setPos(100);

	y += height + 10;
	y += height + 10;
    	_env->addButton(rect<s32>(150, y, 250, y + 32), _tab, MyEventReceiver::GUI_ID_GENERATE_BUTTON, L"Generate", L"Generate world");
    	// Store the appropriate data in a context structure.
    	MyEventReceiver::SAppContext context;
    	context.envRadioBox = envRB;
    	context.timeRadioBox = timeRB;
    	context.climatRadioBox = climatRB;
	context.env = _env;

	// create event receiver
	_receiver = new MyEventReceiver(this, context);
	device->setEventReceiver(_receiver);

	//interface set to invisible because camera is active by default
	_tab->setVisible(false);
}

bool Core::isInterfaceVisible() const
{
	return _tab->isVisible();
}

void Core::toggleInterface()
{
	device->getCursorControl()->setVisible(!_tab->isVisible());
	camera->setInputReceiverEnabled(_tab->isVisible());
	_tab->setVisible(!_tab->isVisible());
}
