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
