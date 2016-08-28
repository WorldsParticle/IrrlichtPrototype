#include "Object.h"

Object::Object(IrrlichtDevice *dev): _device(dev), _mesh(NULL), _node(NULL)
{
    _smgr = _device->getSceneManager();
    _position = new vector3d<float>(0, 0, 0);

    _sndChannel = 0;
}

int Object::LoadMesh(std::string meshPath, std::string texturePath)
{
    _mesh = _smgr->getMesh(meshPath.c_str());
    if (_mesh) {
        _node = _smgr->addAnimatedMeshSceneNode(_mesh);
    }
    else {
        std::cout << "ERROR: couldn't load mesh " << meshPath << std::endl;
        return 1;
    }
    if (_node)
    {
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node->setMD2Animation(scene::EMAT_STAND);
        _node->setMaterialTexture(0, _smgr->getVideoDriver()->getTexture(texturePath.c_str()));
        _node->setScale(_node->getScale() * 10);
    }
    else {
        std::cout << "ERROR: couldn't create node for mesh " << meshPath << std::endl;
        return 1;
    }
    return 0;
}

void Object::SetPosition(int x, int y, int z)
{
    _position->X = x;
    _position->Y = y;
    _position->Z = z;
    _node->setPosition(core::vector3df(_position->X, _position->Y, _position->Z));
}

int Object::SetSound(std::string path, FMOD::System *soundSystem)
{
    soundSystem->createSound(path.c_str(), FMOD_3D, 0, &_sound);
    _sound->set3DMinMaxDistance(5.0f * DISTANCEFACTOR, 500.0f * DISTANCEFACTOR);
    _sound->setMode(FMOD_LOOP_NORMAL);
    soundSystem->playSound(_sound, 0, true, &_sndChannel);

    FMOD_VECTOR pos = {_position->X, _position->Y, _position->Z};
    _sndChannel->set3DAttributes(&pos, NULL);
    _sndChannel->setPaused(false);
}
