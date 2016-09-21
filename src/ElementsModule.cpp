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

#include "ElementsModule.h"
#include "Configuration.h"

int ElementsModule::init()
{
	Object	*testObj = new Object(device);
	Object	*testObj2 = new Object(device);

	testObj->LoadMesh(RESOURCES_PATH "/bush.3ds", RESOURCES_PATH "/bushTexture.jpg");
    testObj->SetPosition(2397 * 2, 203 * 2, 2700 * 2);
    _elements.push_back(testObj);
	testObj2->LoadMesh(RESOURCES_PATH "/tree.3ds", RESOURCES_PATH "/treeTexture.jpg");
	testObj2->SetPosition(1847 * 2, 303 * 2, 2180 * 2);
	testObj2->SetSound(RESOURCES_PATH "/drumloop.wav", _soundSystem);
	_elements.push_back(testObj2);
	return 0;
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

