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
	void    SetPosition(float, float, float);
	//Sets the rotation of the object
	void    SetRotation(float, float, float);
	//Sets the scale of the object
	//void    SetScale(float, float, float);
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
	vector3d<float>                 *_rotation;
	vector3d<float>                 *_scale;

    FMOD::Sound                     *_sound;
    FMOD::Channel                   *_sndChannel;
};
