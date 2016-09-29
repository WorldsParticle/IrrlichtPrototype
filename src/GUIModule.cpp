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

#include    "GUIModule.h"
#include    "Configuration.h"
#include    "gui_radiobuttongroup.h"
#include    "gui_radiocheckboxgroup.h"
#include    "MyEventReceiver.h"

#include    <sstream>

GUIModule::GUIModule(IrrlichtDevice *device, scene::ICameraSceneNode *camera) :
    AModule(device, camera),
    _isVisible(true),
    _console(nullptr),
    _tab(nullptr),
    _soundScrollBar(nullptr),
    _musicScrollBar(nullptr)
{

}

GUIModule::~GUIModule(void)
{

}


int
GUIModule::init(void)
{
    auto env = device->getGUIEnvironment();
    env->getSkin()->setFont(env->getFont(RESOURCES_PATH "/fontlucida.png"));
    _console = env->addStaticText(L"FPS   :   0", rect<s32>(20, 20, 250, 120), false, true, 0, -1, true);
    env->addStaticText(L"Press 'I' to toggle interface, 'C' to toggle console", core::rect<s32>(driver->getScreenSize().Width / 2 - 160, 20, driver->getScreenSize().Width / 2 + 160, 40), false, true, 0, -1, false);
    this->createPanel();
    irr::core::vector2d<irr::s32> boxSize(driver->getScreenSize().Width / 5 - 20, driver->getScreenSize().Height / 10 - 20);
    this->createEnvironmentRadioButton(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 2 + 10), boxSize);
    this->createDayTimeRadioButton(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 3 + 10), boxSize);
    this->createWeatherRadioButton(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 4 + 10), boxSize);
    this->createMusicVolumeScrollBar(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 5 + 10), boxSize);
    this->createSoundVolumeScrollBar(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 6 + 10), boxSize);
    this->createGenerateButton(irr::core::vector2d<irr::s32>(10, driver->getScreenSize().Height / 10 * 7 + 10), boxSize);
    this->setPanelVisibility(false);
    return 0;
}

void
GUIModule::createPanel(void)
{
    _tab = env->addTab(core::rect<s32>(driver->getScreenSize().Width - driver->getScreenSize().Width / 5, 0, driver->getScreenSize().Width, driver->getScreenSize().Height));
    _tab->setDrawBackground(true);
    _tab->setBackgroundColor(SColor(255, 140, 140, 140));
    auto img = env->addImage(irr::core::rect<irr::s32>(10, 10, driver->getScreenSize().Width / 5 - 20, driver->getScreenSize().Height / 5 - 10), _tab);
    img->setImage(device->getVideoDriver()->getTexture(RESOURCES_PATH "/2017_logo_worldsparticle.png"));
    img->setScaleImage(true);
}

void
GUIModule::createEnvironmentRadioButton(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();
    const irr::s32 checkBoxWidth = boxSize.X / 3;
    const irr::s32 checkBoxHeight = boxSize.Y;

    CGUIRadioCheckBoxGroup *envRB = new CGUIRadioCheckBoxGroup(env, _tab);
    IGUICheckBox* mountain = env->addCheckBox(false, core::rect<s32>(0, 0, checkBoxWidth, checkBoxHeight), _tab, 0, L"Mountain");
    IGUICheckBox* forest = env->addCheckBox(false, core::rect<s32>(checkBoxWidth, 0, 2 * checkBoxWidth, checkBoxHeight), _tab, 0, L"Forest");
    IGUICheckBox* beach = env->addCheckBox(false, core::rect<s32>(2 * checkBoxWidth, 0, 3 * checkBoxWidth, checkBoxHeight), _tab, 0, L"Beach");
    envRB->add(mountain);
    envRB->add(forest);
    envRB->add(beach);
    envRB->setRelativePosition(core::rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y));
}

void
GUIModule::createDayTimeRadioButton(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();
    const irr::s32 checkBoxWidth = boxSize.X / 3;
    const irr::s32 checkBoxHeight = boxSize.Y;

    CGUIRadioCheckBoxGroup *timeRB = new CGUIRadioCheckBoxGroup(env, _tab);
    IGUICheckBox* day = env->addCheckBox(false, core::rect<s32>(0, 0, checkBoxWidth, checkBoxHeight), _tab, 0, L"Day");
    IGUICheckBox* night = env->addCheckBox(false, core::rect<s32>(checkBoxWidth, 0, 2 * checkBoxWidth, checkBoxHeight), _tab, 0, L"Night");
    timeRB->add(day);
    timeRB->add(night);
    timeRB->setRelativePosition(core::rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y));
}

void
GUIModule::createWeatherRadioButton(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();
    const irr::s32 checkBoxWidth = boxSize.X / 3;
    const irr::s32 checkBoxHeight = boxSize.Y;

    CGUIRadioCheckBoxGroup *climatRB = new CGUIRadioCheckBoxGroup(env, _tab);
    IGUICheckBox* sun = env->addCheckBox(false, core::rect<s32>(0, 0, checkBoxWidth, checkBoxHeight), _tab, 0, L"Sun");
    IGUICheckBox* rain = env->addCheckBox(false, core::rect<s32>(checkBoxWidth, 0, 2 * checkBoxWidth, checkBoxHeight), _tab, 0, L"Rain");
    IGUICheckBox* snow = env->addCheckBox(false, core::rect<s32>(2 * checkBoxWidth, 0, 3 * checkBoxWidth, checkBoxHeight), _tab, 0, L"Snow");
    climatRB->add(sun);
    climatRB->add(rain);
    climatRB->add(snow);
    climatRB->setRelativePosition(core::rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y));
}

void
GUIModule::createMusicVolumeScrollBar(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();

    env->addStaticText(L"Music volume", rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y / 2), false, true, _tab);
    _musicScrollBar = env->addScrollBar(true, rect<s32>(boxOffset.X, boxOffset.Y + boxSize.Y / 2, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y), _tab, MyEventReceiver::GUI_ID_MUSIC_SCROLL_BAR);
    _musicScrollBar->setMax(255);
    _musicScrollBar->setPos(255);
}

void
GUIModule::createSoundVolumeScrollBar(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();


    env->addStaticText(L"Sound volume", rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y / 2), false, true, _tab);
    _soundScrollBar = env->addScrollBar(true, rect<s32>(boxOffset.X, boxOffset.Y + boxSize.Y / 2, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y), _tab, MyEventReceiver::GUI_ID_SOUND_SCROLL_BAR);
    _soundScrollBar->setMax(255);
    _soundScrollBar->setPos(255);
}

void
GUIModule::createGenerateButton(const irr::core::vector2d<irr::s32> boxOffset, const irr::core::vector2d<irr::s32> boxSize)
{
    auto env = device->getGUIEnvironment();

    env->addButton(rect<s32>(boxOffset.X, boxOffset.Y, boxOffset.X + boxSize.X, boxOffset.Y + boxSize.Y), _tab, MyEventReceiver::GUI_ID_GENERATE_BUTTON, L"Generate", L"Generate world");
}

int
GUIModule::update(void)
{
    auto driver = device->getVideoDriver();
    auto driverType = driver->getDriverType();

    std::wstringstream   ss;

    ss << "FPS : " << driver->getFPS() << '\n'
        << "Driver Type : " << (driverType == EDT_DIRECT3D9 ? "DIRECT3D9" : "OPENGL") << "\n"
        << "Dynamic Lights : " << driver->getDynamicLightCount() << '/' << driver->getMaximalDynamicLightAmount() << "\n"
        << "Primitives : " << driver->getPrimitiveCountDrawn() << '/' << driver->getMaximalPrimitiveCount() << '\n'
        << "Resolution : " << driver->getScreenSize().Width << "x" << driver->getScreenSize().Height;
    _console->setText(ss.str().c_str());
    return 0;
}