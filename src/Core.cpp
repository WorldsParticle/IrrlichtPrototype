#include "Core.h"
#include "interface/MyEventReceiver.h"
#include "module/ElementsModule.h"
#include "module/SkyboxModule.h"
#include "module/TerrainModule.h"
#include "module/WaterModule.h"
#include "module/SoundModule.h"
#include "module/ParticleModule.h"
#include "module/TimerModule.h"
#include "interface/gui_radiocheckboxgroup.h"
#include "generator/generator.h"
#include "map/map.h"
#include "shaders/CustomTreeShader.h"
#include "shaders/CustomLeafShader.h"

// Moche, a sortir quand on allegera le core
#include "generator/step/zoningstep.h"
#include "generator/step/shaperstep.h"
#include "generator/step/elevatorstep.h"
#include "generator/step/riverorstep.h"
#include "generator/step/moistorstep.h"
#include "generator/step/biomizatorstep.h"
#include "generator/step/heightmapingstep.h"
#include "generator/step/texturestep.h"
#include "generator/param/intvalue.h"

#include "Configuration.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace gen;

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
	_driver->setFog(video::SColor(255,255 / 5,255 / 5, 255 / 5),EFT_FOG_LINEAR, WP_CAM_FARVALUE / 8, WP_CAM_FARVALUE * 0.8, 0.5, true, true);

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

	// Temporary, for the forum
	scene::ILightSceneNode *light = _smgr->addLightSceneNode(0,
																													WP_SUN_POSITION,
																													WP_SUN_COLOR,
																													WP_SUN_RADIUS);
	std::cout << "Directionnal light added : " << light << std::endl; // hardcore warning removal


	camera = _smgr->addCameraSceneNodeFPS(0, 100.0f, WP_CAM_DEV_SPEED, -1, keyMap, 8); // 0.5
	camera->setFarValue(WP_CAM_FARVALUE);

	//camera->setPosition(core::vector3df(_worldSettings.OriginX, _worldSettings.OriginY, -_worldSettings.OriginZ));
	//camera->setTarget(core::vector3df(_worldSettings.OriginX, 0, -_worldSettings.OriginZ));
	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	//
	//MODULES
	//
	//Add light
	_smgr->setAmbientLight(video::SColorf(0.2,0.2,0.2, 1));

    if (CustomTreeShader::Initialize(this->_driver->getGPUProgrammingServices()) == false)
    {
        std::cout << "Failed to initialize CustomTreeShader" << std::endl;
    }
    if (CustomLeafShader::Initialize(this->_driver->getGPUProgrammingServices()) == false)
    {
        std::cout << "Failed to initialize CustomLeafShader" << std::endl;
    }

    timerModule = new TimerModule(this, device, camera);
    timerModule->init();
	soundModule = new SoundModule(this, device, camera);
	soundModule->init();
	soundModule->AddBGMusic(RESOURCES_PATH "/sound/river_bg.ogg");
	skyboxModule = new SkyboxModule(this, device, camera, timerModule);
	skyboxModule->init();
	terrainModule = new TerrainModule(this, device, camera);
	terrainModule->init();
	elementsModule = new ElementsModule(this, device, camera, soundModule->soundSystem, terrainModule);
	elementsModule->init();
	waterModule = new WaterModule(this, device, camera, terrainModule);
	waterModule->init();
	particleModule = new ParticleModule(this, device, camera, timerModule);
	particleModule->init();
    


	setGUI();

	return 0;
}

int	Core::initGenerator()
{
	map = nullptr;
	generator = new Generator();

	generator->steps().push_back(new ZoningStep("Zones"));
	generator->steps().push_back(new ShaperStep("Shape"));
	generator->steps().push_back(new ElevatorStep("Elevation"));
	generator->steps().push_back(new RiverorStep("Rivers"));
	generator->steps().push_back(new MoistorStep("Moistor"));
	generator->steps().push_back(new BiomizatorStep("Bioming"));
	generator->steps().push_back(new HeightMapingStep("Heightmap"));
	generator->steps().push_back(new TextureStep("Textures"));

	return 0;
}

void Core::generate()
{
	// apply gui value
	// todo
	dynamic_cast<IntValue *>(generator->step("Zones")->param("Nombre"))->setValue(200);

	if (map)
		delete map;

	map = generator->run(WP_MAP_SIZE, WP_MAP_SIZE);
	terrainModule->generateFromMap(*map);

	camera->setPosition(vector3df(WP_TERRAIN_SIZE / 2,
															  terrainModule->getHeight(WP_TERRAIN_SIZE / 2, WP_TERRAIN_SIZE / 2) + WP_TERRAIN_SCALE,
																WP_TERRAIN_SIZE / 2));
	camera->setTarget(vector3df(0, terrainModule->getHeight(WP_TERRAIN_SIZE / 2, WP_TERRAIN_SIZE / 2), 0));
	elementsModule->generateDouglasFirTree();

	applyFogRec(_smgr->getRootSceneNode());
	skyboxModule->skybox()->setMaterialFlag(video::EMF_FOG_ENABLE, false); // Bad Workaround

	_receiver->switchCameraMode(); // Carefull, remove when we will have a camera class. It suppose we are in dev mode
}

int Core::run()
{
	int lastFPS = -1;

	generate();
	while (device->run())
		if (device->isWindowActive())
		{
            timerModule->update();
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

	//Check box for switching to wireframe mode
	IGUICheckBox *wireframe = _env->addCheckBox(false, core::rect<s32>(3 * width, 0, width, height), _tab, 0, L"Wireframe mode");
	envRB->add(wireframe);

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
    	_env->addButton(rect<s32>(130, y, 270, y + 32), _tab, MyEventReceiver::GUI_ID_GENERATE_BUTTON, L"Generate", L"Generate world");
	y += height + 10;
	y += height + 10;
    	_env->addButton(rect<s32>(130, y, 270, y + 32), _tab, MyEventReceiver::GUI_ID_APPLY_PARAMS_BUTTON, L"Apply parameters", L"Apply parameters without generating a new world");
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

void Core::applyFogRec(ISceneNode *node)
{
	if (!node)
	        return;

	    node->setMaterialFlag(video::EMF_FOG_ENABLE, true);

	    const core::list<scene::ISceneNode*> & children = node->getChildren();
	    core::list<scene::ISceneNode*>::ConstIterator it = children.begin();
	    for (; it != children.end(); ++it)
	        applyFogRec(*it);
}
