#pragma once

#include <list>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>

#include "AModule.h"
#include "Object.h"
#include "TerrainModule.h"

class ElementsModule : public AModule
{
public:
	struct SObjectInfo
	{
		float densityInPercent;
		std::string modelPath;
		std::string texturePath;
		std::string soundPath;
	};
	ElementsModule(IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera, FMOD::System *sndSystem,
		TerrainModule *terrain)
		: AModule(_device, _camera), _soundSystem(sndSystem), _terrain(terrain)
	{}
	~ElementsModule()
	{ clear(); }

	virtual int init();
	virtual int update();

	//Sets the volume of the sound of all the objects in the list
	void SetVolume(float);
	void putElementsOfZone(int zone);
	void clear();
	void createObjectsFromName(int totalElementInZone, int width, int height, SObjectInfo const &objInfo);
private:
	float waterHeight = 300;
    list<std::shared_ptr<Object>>	_elements;
	FMOD::System	*_soundSystem;
	TerrainModule	*_terrain;
	std::vector<std::vector<SObjectInfo>> _objectsInfoByZone;
	glm::vec3 getXYPos(int width, int height);
};
