
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
	params.WindowSize = core::dimension2d<u32>(640, 480);
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
	camera =
		smgr->addCameraSceneNodeFPS(0, 100.0f, 1.2f);
	//smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	camera->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));
	camera->setTarget(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));
	camera->setFarValue(42000.0f);

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	//
	//MODULES
	//

	elementsModule = new ElementsModule(device, driver, smgr, env, camera);
	elementsModule->init();
	skyboxModule = new SkyboxModule(device, driver, smgr, env, camera);
	skyboxModule->init();


	// create event receiver
	//MyEventReceiver receiver(terrain, skybox, skydome);
	//device->setEventReceiver(&receiver);

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

			driver->beginScene(true, true, 0);

			smgr->drawAll();
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

void Core::drop()
{
	device->drop();
}