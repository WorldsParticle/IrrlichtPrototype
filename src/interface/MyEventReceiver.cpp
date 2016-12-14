#include "interface/MyEventReceiver.h"
#include "Core.h"
#include "module/SkyboxModule.h"
#include "module/ParticleModule.h"
#include "module/TerrainModule.h"
#include "module/SoundModule.h"
#include "module/ElementsModule.h"
#include "module/WaterModule.h"
#include "scene/water/WaterNode.h"
#include <iostream>

using namespace irr;

MyEventReceiver::MyEventReceiver(Core *core, SAppContext & context)
	: _core(core), _context(context)
{
}

void MyEventReceiver::ApplyGUIParametersToWorld()
{
	std::cout << "Environment: " << _context.envRadioBox->getSelected() << std::endl;
	std::cout << "Time: " << _context.timeRadioBox->getSelected() << std::endl;
	std::cout << "Climat: " << _context.climatRadioBox->getSelected() << std::endl;
    _core->timerModule->setTime(0); // Will later get new time from UI
	_core->skyboxModule->setSkybox(_context.timeRadioBox->getSelected(),
			_context.climatRadioBox->getSelected()); // Will later only get weather value
	_core->particleModule->setWeather(_context.climatRadioBox->getSelected());
	_core->soundModule->SetEnvironmentalSound(_context.envRadioBox->getSelected(),
			_context.timeRadioBox->getSelected(),
			_context.climatRadioBox->getSelected());
	//_core->elementsModule->putElementsOfZone(_context.envRadioBox->getSelected());
	_core->elementsModule->generateDouglasFirTree();
}

void MyEventReceiver::Generate()
{
	_core->generate();
	//generatorModule->buildTerrain(_context.envRadioBox->getSelected());
	ApplyGUIParametersToWorld();
}
bool MyEventReceiver::OnEvent(const SEvent& event)
{
	// check if user presses the key 'W' or 'D'
	if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
	{
		switch (event.KeyInput.Key)
		{
	  case irr::KEY_KEY_C: // switch camera
			//switchCameraMode();
			return true;
		case irr::KEY_KEY_V: // switch wireframe mode
			switchWireframe();
			return true;
		case irr::KEY_ESCAPE: // quit
			_core->close(); //comment this to get the confirmation before quitting back
			if (confirmQuit == nullptr) {
				if (!_core->isInterfaceVisible())
					_core->toggleInterface();
				confirmQuit = _context.env->addWindow(
						rect<s32>(100, 100, 250, 200),
							false, // modal?
							L"Confirm quit");

						_context.env->addStaticText(L"Do you want to quit ?",
							rect<s32>(10,35,170,50),
							false, // border?
							true, // wordwrap?
							confirmQuit);
						_context.env->addButton(rect<s32>(30, 60, 60, 80), confirmQuit, MyEventReceiver::GUI_ID_QUIT, L"Yes", L"Quit");
						_context.env->addButton(rect<s32>(70, 60, 100, 80), confirmQuit, MyEventReceiver::GUI_ID_BACK, L"No", L"Cancel");
			} else {
			    confirmQuit->remove();
			    confirmQuit = nullptr;
			}
			return true;
		case irr::KEY_KEY_I: // interface
			_core->toggleInterface();
			return true;
		default:
			break;
		}
	}
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
					case GUI_ID_GENERATE_BUTTON:
						Generate();
						return true;
					case GUI_ID_APPLY_PARAMS_BUTTON:
						ApplyGUIParametersToWorld();
						return true;

					case GUI_ID_QUIT:
						_core->close();

					case GUI_ID_BACK:
						confirmQuit->remove();
						confirmQuit = nullptr;

					default:
						return false;
				}
				break;

			case EGET_SCROLL_BAR_CHANGED:
				if (id == GUI_ID_MUSIC_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					_core->soundModule->SetVolume((float)pos / 100.0);
					std::cout << "Music volume: " << pos << std::endl;
				}
				else if (id == GUI_ID_SOUND_SCROLL_BAR)
				{
					s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					_core->elementsModule->SetVolume((float)pos / 100.0);
					std::cout << "Sound volume: " << pos << std::endl;
				}
				break;

			default:
				break;
		}
	}

	return false;
}

void MyEventReceiver::switchWireframe()
{
	static bool wireframe = false;
	wireframe = !wireframe;

	for (scene::ITerrainSceneNode *node : _core->terrainModule->terrainGridNodes())
		node->setMaterialFlag(EMF_WIREFRAME, wireframe);
	for (WaterNode *node: _core->waterModule->waterNodes())
		node->waterNode()->setMaterialFlag(EMF_WIREFRAME, wireframe);
}

void MyEventReceiver::switchCameraMode()
{
	// clunky, waiting for better archi to make better code
	static bool freeCam = true;
	freeCam = !freeCam;

	for (ISceneNodeAnimator *anim : _core->camera->getAnimators())
	{
		if (anim->getType() == ESNAT_COLLISION_RESPONSE)
			reinterpret_cast<ISceneNodeAnimatorCollisionResponse *> (anim)->setGravity(core::vector3df(0, freeCam ? 0 : -30, 0));
		else if (anim->getType() == ESNAT_CAMERA_FPS)
		{
			reinterpret_cast<ISceneNodeAnimatorCameraFPS *> (anim)->setVerticalMovement(freeCam);
			reinterpret_cast<ISceneNodeAnimatorCameraFPS *> (anim)->setMoveSpeed(freeCam ? WP_CAM_DEV_SPEED : WP_CAM_EXPLO_SPEED);
		}
	}
}
