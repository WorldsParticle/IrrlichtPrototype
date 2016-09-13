#pragma once

#include <string>
#include <irrlicht.h>
#include "SoundModule.h"

using namespace irr;

class Object
{
public:
    Object(IrrlichtDevice *);
    ~Object();
    int     LoadMesh(std::string, std::string);
    void    SetPosition(int, int, int);
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
