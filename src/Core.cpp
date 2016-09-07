#include "Core.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int Core::initIrrlicht(){
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

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	env = device->getGUIEnvironment();

	return 0;
}

int Core::initModules()
{
	/*
	First, we add standard stuff to the scene: A nice irrlicht engine
	logo, a small help text, a user controlled camera, and we disable
	the mouse cursor.
	*/

	//
	// BASIC ENVIRONNEMENT
	//
	device->setWindowCaption(L"WorldsParticle prototype");

	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	// add irrlicht logo
	env->addImage(driver->getTexture("./ressources/irrlichtlogo2.png"),
		core::position2d<s32>(10, 10));

	//set other font
	env->getSkin()->setFont(env->getFont("./ressources/fontlucida.png"));

	// add some help text
	//env->addStaticText(
	//	L"Press 'W' to change wireframe mode\nPress 'D' to toggle detail map\nPress 'S' to toggle skybox/skydome",
	//	core::rect<s32>(10, 421, 250, 475), true, true, 0, -1, true);

	//
	// CAMERA
	//
    irr::SKeyMap keyMap[5];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_KEY_Z;
    keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_S;
    keyMap[2].Action = irr::EKA_STRAFE_LEFT;
    keyMap[2].KeyCode = irr::KEY_KEY_Q;
    keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[3].KeyCode = irr::KEY_KEY_D;
    keyMap[4].Action = irr::EKA_JUMP_UP;
    keyMap[4].KeyCode = irr::KEY_SPACE;
	camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f, -1, keyMap, 5);
	//smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	camera->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));
	camera->setTarget(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));
	camera->setFarValue(42000.0f);

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);
	//camera->setInputReceiverEnabled(false);

	//
	//MODULES
	//
	//Add light so we can see the nice water
	smgr->setAmbientLight(video::SColorf(0.6,0.6,0.6,1));

	soundModule = new SoundModule(device, camera);
	soundModule->init();
    soundModule->AddBGMusic("ressources/river_bg.ogg");
	elementsModule = new ElementsModule(device, camera, soundModule->soundSystem);
	elementsModule->init();
	skyboxModule = new SkyboxModule(device, camera);
	skyboxModule->init();
	terrainModule = new TerrainModule(device, camera);
	terrainModule->init();
	waterModule = new WaterModule(device, camera, terrainModule);
	waterModule->init();
    particleModule = new ParticleModule(device, camera);
    particleModule->init();

	//set GUI
    	env->addButton(rect<s32>(10,240,110,240 + 32), 0, MyEventReceiver::GUI_ID_QUIT_BUTTON,
    	    	    L"Quit", L"Exits Program");
    	//env->addButton(rect<s32>(10,280,110,280 + 32), 0, MyEventReceiver::GUI_ID_NEW_WINDOW_BUTTON,
    	//		L"New Window", L"Launches a new Window");
    	env->addButton(rect<s32>(10,320,110,320 + 32), 0, MyEventReceiver::GUI_ID_FILE_OPEN_BUTTON,
    	    	    L"File Open", L"Opens a file");
    	env->addStaticText(L"Logging ListBox:", rect<s32>(50,110,250,130), true);
    	IGUIListBox * listbox = env->addListBox(rect<s32>(50, 140, 250, 210));
    	env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

    	// Store the appropriate data in a context structure.
    	MyEventReceiver::SAppContext context;
    	context.device = device;
    	context.counter = 0;
    	context.listbox = listbox;
	// create event receiver
	receiver = new MyEventReceiver(this, context);
	device->setEventReceiver(receiver);

	return 0;
}

int Core::run()
{

	/*
	That's it, draw everything.
	*/

	int lastFPS = -1;

	while (device->run())
		if (device->isWindowActive())
		{
			elementsModule->update();
			skyboxModule->update();
			terrainModule->update();
            particleModule->update();
			soundModule->update();

			driver->beginScene(true, true, 0);

			smgr->drawAll();
			if (isInterfaceActive)
			    env->drawAll();

			driver->endScene();

			// display frames per second in window title
			int fps = driver->getFPS();
			if (lastFPS != fps)
			{
				core::stringw str = L"WorldsParticle prototype [";
				str += driver->getName();
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
