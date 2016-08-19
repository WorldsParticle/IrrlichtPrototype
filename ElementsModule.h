#pragma once

#include "AModule.h"

class ElementsModule : public AModule
{
public:
	ElementsModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera)
		: AModule(_device, _camera)
	{}
	~ElementsModule()
	{}

	virtual int init();
	virtual int update();

private:

};
