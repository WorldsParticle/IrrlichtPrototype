#include <algorithm>
#include <iostream>
#include <ctime>

#include "shaders/CustomTreeShader.h"
#include "shaders/CustomLeafShader.h"
#include "module/ElementsModule.h"
#include "Configuration.h"

#include "Core.h"
#include "module/TerrainModule.h"

#include "WorldSettings.h"

float ElementsModule::getRandom(float &totalPercent, float nbElem)
{
	float maxPercent = totalPercent;
	if (maxPercent > 100.0f - nbElem * 20.0f)
		maxPercent = 100.0f - nbElem * 20.0f;
	float percent = static_cast<float>(rand() % (static_cast<int>(maxPercent) - 20)) + 20.0f;
	totalPercent -= percent;
	return percent;
}

int ElementsModule::init()
{
	float a = 100.0f, b = 100.0f, c = 100.0f;
	_objectsInfoByZone = { //first number is the density of the element in the given environment
		{
			{ getRandom(a, 3.0f), RESOURCES_PATH "/models/Rock1.obj", "", ""},
			{ getRandom(a, 3.0f), RESOURCES_PATH "/models/Tree1.obj", "", ""},
			{ a, RESOURCES_PATH "/models/tree.3ds", RESOURCES_PATH "/models/treeTexture.jpg", ""}
		}, //zone 0 : mountain
		{
			{ getRandom(b, 2.0f), RESOURCES_PATH "/models/Rock2.obj", "", ""},
			{ b, RESOURCES_PATH "/models/Tree2.obj", "", ""}
		}, //zone 1 : forest
		{
			{ getRandom(c, 3.0f), RESOURCES_PATH "/models/Tree3.obj", "", RESOURCES_PATH "/sound/cicadas.mp3" },
			{ getRandom(c, 3.0f), RESOURCES_PATH "/models/Rock3.obj", "", ""},
			{ c, RESOURCES_PATH "/models/bush.3ds", RESOURCES_PATH "/models/bushTexture.jpg", ""}
		} //zone 2 : beach
		};
	srand(static_cast<unsigned int>(time(nullptr)));
	putElementsOfZone(0);

    //this->generateDouglasFirTree();

	return 0;
}

#include <IMeshBuffer.h>


//
// ROOT_NODE
// |-> DouglasFirNode
//     |-> DouglasFirBarkNode
//     |-> DouglasFirNeedlesNode
//
// MeshBuffer(0) -> Bark
// MeshBuffer(1) -> Bark collision
// MeshBuffer(2) -> Bending proxy
// MeshBuffer(3) -> Bark low lod
// MeshBuffer(4) -> Needles LOD 1
// MeshBuffer(5) -> Bark branch
// MeshBuffer(6) -> Needles LOD 0
void
ElementsModule::generateDouglasFirTree(void)
{
    auto raw_mesh = smgr->getMesh(RESOURCES_PATH "/models/Trees/DouglasFir/HEO_DouglasFir.obj");
    auto mesh = smgr->getMeshManipulator()->createMeshWithTangents(raw_mesh);

    //irr::io::IAttributes &attributes = const_cast<irr::io::IAttributes &>(driver->getDriverAttributes());
    //std::cout << "ShaderLanguageVersion : " << attributes.getAttributeAsString("ShaderLanguageVersion").c_str() << std::endl;

    // generate a DouglasFir_node
    {

        auto DouglasFirNode = this->smgr->addEmptySceneNode();
        DouglasFirNode->setName("DouglasFirNode");

        // generate the DouglasFirBarkNode

        irr::scene::SMesh   *barkMesh = new irr::scene::SMesh();
        barkMesh->addMeshBuffer(mesh->getMeshBuffer(0));
        barkMesh->addMeshBuffer(mesh->getMeshBuffer(5));
        auto DouglasFirBarkNode = this->smgr->addMeshSceneNode(barkMesh, DouglasFirNode);
        DouglasFirBarkNode->setName("DouglasFirBarkNode");
        DouglasFirBarkNode->setMaterialType(CustomTreeShader::GetMaterialType());
        DouglasFirBarkNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/DouglasFir/DouglasFirBark_diffuse.png"));
        DouglasFirBarkNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/DouglasFir/DouglasFirBark_normals.png"));

        // generate the DouglasFirNeedlesNode
        irr::scene::SMesh   *needlesMesh = new irr::scene::SMesh();
        needlesMesh->addMeshBuffer(mesh->getMeshBuffer(4));
        needlesMesh->addMeshBuffer(mesh->getMeshBuffer(6));
        auto DouglasFirNeedlesNode = this->smgr->addMeshSceneNode(needlesMesh, DouglasFirNode);
        DouglasFirNeedlesNode->setName("DouglasFirNeedlesNode");
        DouglasFirNeedlesNode->setMaterialType(CustomLeafShader::GetMaterialType());
        DouglasFirNeedlesNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/DouglasFir/DouglasFirNeedles_diffuse.png"));
        DouglasFirNeedlesNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/DouglasFir/DouglasFirNeedles_normals.png"));
        DouglasFirNeedlesNode->setMaterialTexture(2, driver->getTexture(RESOURCES_PATH "/models/Trees/DouglasFir/DouglasFirNeedles_alpha.png"));

        // Settings not needed at the end.

        DouglasFirNode->setPosition(irr::core::vector3df(5000.0f, -5000.0f, 5000.0f));
        DouglasFirNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));

        std::cout << "DouglasFir absolute position : (" << DouglasFirNode->getAbsolutePosition().X << ", " << DouglasFirNode->getAbsolutePosition().Y << ", " << DouglasFirNode->getAbsolutePosition().Z << ")" << std::endl;
        std::cout << "DouglasFir position : (" << DouglasFirNode->getPosition().X << ", " << DouglasFirNode->getPosition().Y << ", " << DouglasFirNode->getPosition().Z << ")" << std::endl;
        std::cout << "DouglasFir scale : (" << DouglasFirNode->getScale().X << ", " << DouglasFirNode->getScale().Y << ", " << DouglasFirNode->getScale().Z << ")" << std::endl;


        for (int i = 0; i < (WP_TERRAIN_SCALE * 10) ; ++i)
        {
            auto node = DouglasFirNode->clone();
            glm::vec2 new_position = glm::linearRand(glm::vec2(0.0f), glm::vec2(WP_TERRAIN_SIZE));
						f32 	height = core->terrainModule->getHeight(new_position.x, new_position.y);
						if (height > WP_SEA_HEIGHT)
						{
            	node->setPosition(irr::core::vector3df(new_position.x,
																									core->terrainModule->getHeight(new_position.x, new_position.y),
																									new_position.y));
							float randomScale = ( (float)( (rand() % 10) + 5 ) ) / 10.0f; // 0.5~1.4
            	node->setScale(irr::core::vector3df(WP_ELEMENT_SCALE * randomScale));
						}
        }

    }
}

void ElementsModule::putElementsOfZone(int zone)
{
	if (_elements.size() > 0)
		clear();
	for (auto const &objInfo : _objectsInfoByZone[zone])
	{
		createObjectsFromName(5, 10000, 10000, objInfo); //nbTotalElements, width, height
	}
	SetVolume(_soundVolume);
}

void ElementsModule::clear()
{
	for (std::shared_ptr<Object> obj : _elements)
	{
		obj->remove();
	}
	_elements.clear();
}

int ElementsModule::update()
{
	//nothing to do
	return 0;
}

void ElementsModule::SetVolume(float vol)
{
	_soundVolume = vol;
	for (std::shared_ptr<Object> elem : _elements)
	{
		elem->SetVolume(vol);
	}
}

glm::vec3 ElementsModule::getXYPos(int width, int height)
{
	glm::vec3 value = glm::linearRand(
			glm::vec3(50, 50, 0),
			glm::vec3(width, height, 360));
	//get position in xy between 50 and width/height and rotation angle between 0 and 360

	int isThisOnlyWater = 50;
	//while (_terrain->getHeight(value.x, value.y) < waterHeight && isThisOnlyWater > 0)
	while (0 < WP_SEA_HEIGHT && isThisOnlyWater > 0)
	{
		value = glm::linearRand(glm::vec3(50, 50, 0), glm::vec3(width, height, 0));
		--isThisOnlyWater;
	}
	return value;
}

void ElementsModule::SetupObject(glm::vec3 const &randomValue, std::shared_ptr<Object> obj, SObjectInfo const &objInfo)
{
	obj->SetPosition(randomValue.x, _terrain->getHeight(randomValue.x, randomValue.y), randomValue.y);
	//obj->SetPosition(randomValue.x, 0, randomValue.y);
	obj->SetRotation(0, randomValue.z, 0);
	if (objInfo.soundPath != "")
		obj->SetSound(objInfo.soundPath, _soundSystem);
	_elements.push_back(obj);
}

void ElementsModule::createObjectsFromName(int totalElementInZone, int width, int height, SObjectInfo const &objInfo)
{
	std::shared_ptr<Object> firstObj = std::make_shared<Object>(device);

	if (firstObj->LoadMesh(objInfo.modelPath, objInfo.texturePath) == 1)
	{
		firstObj->remove();
		return;
	}
	int elemCount = static_cast<int>(objInfo.densityInPercent * totalElementInZone / 100);
	//std::cout << ">> Number of elements " << elemCount << std::endl;
	while (elemCount > 0)
	{
		glm::vec3 randomValue = getXYPos(width, height);
		if (elemCount != objInfo.densityInPercent * totalElementInZone / 100)
		{
			std::shared_ptr<Object> obj = std::make_shared<Object>(device);
			if (obj->LoadMesh(*firstObj) == 1)
			{
				obj->remove();
				return;
			}
			SetupObject(randomValue, obj, objInfo);
		}
		else
		{
			SetupObject(randomValue, firstObj, objInfo);
		}

		--elemCount;
	}
}
