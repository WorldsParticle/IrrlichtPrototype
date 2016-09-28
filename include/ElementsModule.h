#pragma once

#include <list>
#include "AModule.h"
#include "Object.h"

class ElementsModule : public AModule
{
public:
	ElementsModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera, FMOD::System *sndSystem)
		: AModule(_device, _camera), _soundSystem(sndSystem)
	{}
	~ElementsModule()
	{}

	virtual int init();
	virtual int update();

	//Sets the volume of the sound of all the objects in the list
	void SetVolume(float);
private:
    list<Object *>	_elements;
	FMOD::System	*_soundSystem;
};
