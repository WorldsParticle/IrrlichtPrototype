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

#include    <sstream>

GUIModule::GUIModule(IrrlichtDevice *device, scene::ICameraSceneNode *camera) :
    AModule(device, camera),
    _isVisible(true)
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
    return 0;
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






