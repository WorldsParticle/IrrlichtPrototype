#pragma once

#include <list>
#include "AModule.h"
#include "Object.h"
#include "TerrainModule.h"

class ElementsModule : public AModule
{
public:
	ElementsModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera, FMOD::System *sndSystem,
		TerrainModule *terrain)
		: AModule(_device, _camera), _soundSystem(sndSystem), _terrain(terrain)
	{}
	~ElementsModule()
	{}

	virtual int init();
	virtual int update();

	//Sets the volume of the sound of all the objects in the list
	void SetVolume(float);
	void createObjectsFromName(int totalElementInZone, int width, int height, int density, std::string const &modelPath, std::string const &texturePath, std::string const &soundPath);
private:
    list<Object *>	_elements;
	FMOD::System	*_soundSystem;
	TerrainModule	*_terrain;
};
