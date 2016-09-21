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

#include "Core.h"
#include "MyEventReceiver.h"
#include "ElementsModule.h"
#include "SkyboxModule.h"
#include "TerrainModule.h"
#include "WaterModule.h"
#include "SoundModule.h"
#include "ParticleModule.h"
#include "Configuration.h"

#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Core::Core(int argc, char *argv[]) :
    _receiver(nullptr),
    _elementsModule(nullptr),
    _skyboxModule(nullptr),
    _terrainModule(nullptr),
    _waterModule(nullptr),
    _soundModule(nullptr),
    _particleModule(nullptr),
    _isInterfaceActive(false),
    _device(nullptr),
    _windowSize(1280, 720),
    _fullscreen(false)
{
    if (argc == 2 && std::string(argv[1]) == "fullscreen")
    {
        IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
        if (nulldevice != nullptr)
        {
            _windowSize = nulldevice->getVideoModeList()->getDesktopResolution();
            _fullscreen = true;
            nulldevice->drop();
        }
    }
}

Core::~Core(void)
{
    if (_device != nullptr)
    {
        _device->drop();
    }
}



int Core::run()
{
    this->createIrrlichtDevice();
    this->createFPSCamera();
    this->initIrrlicht();
    this->initModules();
    return this->gameLoop();
}

void    Core::initIrrlicht(void)
{
//    _driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
//    _env->getSkin()->setFont(_env->getFont(RESOURCES_PATH "/fontlucida.png"));
    _device->getCursorControl()->setVisible(false);
//    _smgr->setAmbientLight(video::SColorf(0.6f, 0.6f, 0.6f, 1.0f));

    //set GUI
//    _env->addButton(rect<s32>(10, 240, 110, 240 + 32), 0, MyEventReceiver::GUI_ID_QUIT_BUTTON,
//        L"Quit", L"Exits Program");
    //_env->addButton(rect<s32>(10,280,110,280 + 32), 0, MyEventReceiver::GUI_ID_NEW_WINDOW_BUTTON,
    //		L"New Window", L"Launches a new Window");
//    _env->addButton(rect<s32>(10, 320, 110, 320 + 32), 0, MyEventReceiver::GUI_ID_FILE_OPEN_BUTTON,
//        L"File Open", L"Opens a file");

//    auto text = _env->addStaticText(L"FPS:", rect<s32>(50, 110, 250, 130), true);

//    IGUIListBox *listbox = _env->addListBox(rect<s32>(50, 140, 250, 210));
//    _env->addEditBox(L"Editable Text", rect<s32>(350, 80, 550, 100));

    // Store the appropriate data in a context structure.
    MyEventReceiver::SAppContext context;
    context.device = _device;
    context.counter = 0;
    // create event receiver
    _receiver = new MyEventReceiver(this, context);
    _device->setEventReceiver(_receiver);
}

void    Core::createIrrlichtDevice(void)
{
    irr::SIrrlichtCreationParameters params;
    params.AntiAlias = true;
    params.Bits = 16;
    params.DeviceType = EIDT_BEST;
    params.Doublebuffer = true;
    params.DriverMultithreaded = false;
    //  params.DriverType = irr::IrrlichtDevice::isDriverSupported(EDT_DIRECT3D9) ? EDT_DIRECT3D9 : EDT_OPENGL;
    params.DriverType = EDT_OPENGL;
    params.Fullscreen = _fullscreen;
    params.HandleSRGB = false;
    params.HighPrecisionFPU = true;
    params.IgnoreInput = false;
    params.LoggingLevel = ELL_DEBUG;
    params.Stencilbuffer = true;
    params.Stereobuffer = false;
    params.Vsync = true;
    params.WindowSize = _windowSize;
    params.WithAlphaChannel = false; // can be useful later.
    params.ZBufferBits = 16;
    if ((_device = createDeviceEx(params)) == nullptr)
    {
        throw std::runtime_error("could not create irrlicht driver.");
    }
    _device->setWindowCaption(L"WorldsParticle");
}

void    Core::createFPSCamera(void)
{
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

    auto camera = _device->getSceneManager()->addCameraSceneNodeFPS(0, 100.0f, 1.2f, -1, keyMap, 8);
    camera->setPosition(core::vector3df(2700 * 2, 255 * 2, 2600 * 2));
    camera->setTarget(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));
    camera->setFarValue(42000.0f);
}

int Core::initModules()
{
    auto camera = _device->getSceneManager()->getActiveCamera();

    _soundModule = new SoundModule(_device, camera);
    _soundModule->init();
    _soundModule->AddBGMusic(RESOURCES_PATH "/river_bg.ogg");
    _elementsModule = new ElementsModule(_device, camera, _soundModule->soundSystem);
    _elementsModule->init();
    _skyboxModule = new SkyboxModule(_device, camera);
    _skyboxModule->init();
    _terrainModule = new TerrainModule(_device, camera);
    _terrainModule->init();
    _waterModule = new WaterModule(_device, camera, _terrainModule);
    _waterModule->init();
    _particleModule = new ParticleModule(_device, camera);
    _particleModule->init();
	return 0;
}


void    Core::updateModules(void)
{
    _elementsModule->update();
    _skyboxModule->update();
    _terrainModule->update();
    _particleModule->update();
    _soundModule->update();
}

int     Core::gameLoop(void)
{
    auto    driver = _device->getVideoDriver();
    auto    smgr = _device->getSceneManager();
    auto    env = _device->getGUIEnvironment();

    while (_device->run() == true)
    {
        if (_device->isWindowActive() == true)
        {
            updateModules();
            driver->beginScene(true, true, 0);
            smgr->drawAll();
            if (_isInterfaceActive == true)
            {
                env->drawAll();
            }
            driver->endScene();
        }
    }
    return 0;
}
