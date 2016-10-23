#include <iostream>

#include "Object.h"

Object::Object(IrrlichtDevice *dev): _device(dev), _node(NULL)
{
    _smgr = _device->getSceneManager();
	_position = new vector3d<float>(0, 0, 0);
	_rotation = new vector3d<float>(0, 0, 0);

    _sndChannel = 0;
}

Object::~Object()
{
	delete _position;
	delete _rotation;
	//delete _scale;
}

void Object::remove()
{
	if (_node)
	{
		_node->removeAll();
		_node->remove();
	}
}

int Object::LoadMesh(std::string const &meshPath, std::string const &texturePath)
{
    scene::IAnimatedMesh *mesh;
    mesh = _smgr->getMesh(meshPath.c_str());
    if (mesh)
    {
        _node = _smgr->addAnimatedMeshSceneNode(mesh);
    }
    else
    {
        std::cout << "ERROR: couldn't load mesh " << meshPath << std::endl;
        return 1;
    }
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        //_node->setMD2Animation(scene::EMAT_STAND);
		//if (!texturePath.empty())
	 //       _node->setMaterialTexture(0, _smgr->getVideoDriver()->getTexture(texturePath.c_str()));
        _node->setScale(_node->getScale() * 10);
    }
    else
    {
        std::cout << "ERROR: couldn't create node for mesh " << meshPath << std::endl;
        return 1;
    }
    return 0;
}

int     Object::LoadMesh(Object const& other)
{
	_node = other._node->clone();
	if (_node == nullptr)
	{
		std::cout << "ERROR: couldn't clone node " << std::endl;
		return 1;
	}
	return 0;
}


void Object::SetPosition(float x, float y, float z)
{
	_position->X = x;
	_position->Y = y;
	_position->Z = z;
	_node->setPosition(core::vector3df(_position->X, _position->Y, _position->Z));
}
void Object::SetRotation(float x, float y, float z)
{
	_rotation->X = x;
	_rotation->Y = y;
	_rotation->Z = z;
	_node->setRotation(core::vector3df(_rotation->X, _rotation->Y, _rotation->Z));
}
//void Object::SetScale(float x, float y, float z)
//{
//	//TODO
//	//_scale->X = x;
//	//_scale->Y = y;
//	//_scale->Z = z;
//	//_node->setScale(core::vector3df(_scale->X, _scale->Y, _scale->Z));
//}

int Object::SetSound(std::string const &path, FMOD::System *soundSystem)
{
    soundSystem->createSound(path.c_str(), FMOD_3D, 0, &_sound);
    _sound->set3DMinMaxDistance(5.0f * DISTANCEFACTOR, 500.0f * DISTANCEFACTOR);
    _sound->setMode(FMOD_LOOP_NORMAL);
    soundSystem->playSound(_sound, 0, true, &_sndChannel);

    FMOD_VECTOR pos = {_position->X, _position->Y, _position->Z};
    _sndChannel->set3DAttributes(&pos, NULL);
    _sndChannel->setPaused(false);
    return 0;
}

void Object::SetVolume(float vol)
{
    if (_sndChannel != 0)
    {
        _sndChannel->setVolume(vol);
    }
}
