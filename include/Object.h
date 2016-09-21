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

#pragma once

#include <string>
#include <irrlicht.h>
#include "SoundModule.h"

using namespace irr;

//Element that can be placed on the terrain
class Object
{
public:
    Object(IrrlichtDevice *);
    ~Object();
    //Loads a mesh, doesn't set its position
    int     LoadMesh(std::string, std::string);
    //Sets the position of the object
    void    SetPosition(float x, float y, float z);
    //Adds a 3D sound at the position of the object
    int     SetSound(std::string, FMOD::System *);

private:
    Object();

private:
    IrrlichtDevice                  *_device;

    scene::ISceneManager            *_smgr;

    scene::IAnimatedMesh            *_mesh;
    scene::IAnimatedMeshSceneNode   *_node;

    vector3d<float>                 *_position;

    FMOD::Sound                     *_sound;
    FMOD::Channel                   *_sndChannel;
};
