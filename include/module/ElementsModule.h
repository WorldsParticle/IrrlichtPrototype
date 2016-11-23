#pragma once

#include <list>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/random.hpp>

#include "AModule.h"
#include "scene/Object.h"
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
	ElementsModule(Core *c, IrrlichtDevice* _device,
		scene::ICameraSceneNode* _camera, FMOD::System *sndSystem,
		TerrainModule *terrain)
		: AModule(c, _device, _camera), _soundSystem(sndSystem), _terrain(terrain)
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

//private:
/// Generate a DouglasFir Tree in (0,0,0) and returne the parent node.
    ISceneNode  *generateDouglasFirTree(void);
    /// Generate a LargeOak Tree in (0,0,0) and returne the parent node.
    ISceneNode  *generateLargeOakTree(void);
    /// Generate a American Moutain Ash Tree in (0,0,0) and returne the parent node.
    ISceneNode  *generateAmericanMoutainAshTree(void);
    ISceneNode  *generateAmericanSweetgumTree(void);

private:
    glm::vec3   getXYPos(int width, int height);
    void        SetupObject(glm::vec3 const &randomValue, std::shared_ptr<Object> obj, SObjectInfo const &objInfo);
    float       getRandom(float &totalPercent, float nbElem);

private:
	//float                                   waterHeight = 300;
	float                                   _soundVolume = 1.0f;
    list<std::shared_ptr<Object>>	        _elements;
	FMOD::System	                        *_soundSystem;
	TerrainModule	                        *_terrain;
	std::vector<std::vector<SObjectInfo>>   _objectsInfoByZone;
};
