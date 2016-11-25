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

// MeshBuffer(0) -> Person Scale
// MeshBuffer(1) -> Leaf
// MeshBuffer(2) -> Bark
// MeshBuffer(3) -> Collision
// MeshBuffer(4) -> Bark LOD small
// MeshBuffer(5) -> Leaf LOD small
ISceneNode *
ElementsModule::generateAmericanSweetgumTree(void)
{
    auto raw_mesh = smgr->getMesh(RESOURCES_PATH "/models/Trees/AmericanSweetgum/AmericanSweetgum.obj");
    auto mesh = smgr->getMeshManipulator()->createMeshWithTangents(raw_mesh);

    auto AmericanMoutainAshNode = this->smgr->addEmptySceneNode();
    AmericanMoutainAshNode->setName("AmericanSweetgumNode");

    irr::scene::SMesh   *barkMesh = new irr::scene::SMesh();
    barkMesh->addMeshBuffer(mesh->getMeshBuffer(2));

    auto AmericanMoutainAshBarkNode = this->smgr->addMeshSceneNode(barkMesh, AmericanMoutainAshNode);
    AmericanMoutainAshBarkNode->setName("AmericanMoutainAshBarkNode");
    AmericanMoutainAshBarkNode->setMaterialType(CustomTreeShader::GetMaterialType());
    AmericanMoutainAshBarkNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanSweetgum/HEO_AmericanSweetgumBark_Diffuse.png"));
    AmericanMoutainAshBarkNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanSweetgum/HEO_AmericanSweetgumBark_Normal.png"));

    AmericanMoutainAshBarkNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    core::aabbox3df aabb;
    aabb = AmericanMoutainAshBarkNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    AmericanMoutainAshBarkNode->getMesh()->setBoundingBox(aabb);

    irr::scene::SMesh   *needlesMesh = new irr::scene::SMesh();
    needlesMesh->addMeshBuffer(mesh->getMeshBuffer(1));
    auto AmericanMoutainAshLeafNode = this->smgr->addMeshSceneNode(needlesMesh, AmericanMoutainAshNode);
    AmericanMoutainAshLeafNode->setName("AmericanMoutainAshLeafNode");
    AmericanMoutainAshLeafNode->setMaterialType(CustomLeafShader::GetMaterialType());
    AmericanMoutainAshLeafNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanSweetgum/HEO_AmericanSweetgumLeafBunch_Diffuse.png"));
    AmericanMoutainAshLeafNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanSweetgum/HEO_AmericanSweetgumLeafBunch_Normal.png"));
    AmericanMoutainAshLeafNode->setMaterialTexture(2, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanSweetgum/HEO_AmericanSweetgumLeafBunch_AlphaTest.png"));
    AmericanMoutainAshLeafNode->getMaterial(0).BackfaceCulling = false;

    AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    //AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(1)->recalculateBoundingBox();
    aabb = AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    //aabb.addInternalBox(AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(1)->getBoundingBox());
    AmericanMoutainAshLeafNode->getMesh()->setBoundingBox(aabb);

    AmericanMoutainAshNode->setPosition(irr::core::vector3df(0.0f));
    AmericanMoutainAshNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));

    return AmericanMoutainAshNode;
}

//
// ROOT_NODE
// |-> LargeOakTreeNode
//     |-> LargeOakTreeBarkNode
//     |-> LargeOakTreeLeafNode
//     |-> LargeOakTreeTwigsNode
//
// MeshBuffer(0) -> Small Bark -> Useless
// MeshBuffer(1) -> Person Scale
// MeshBuffer(2) -> Proxy
// MeshBuffer(3) -> Full display of twigs -> Useless
// MeshBuffer(4) -> Twigs arbre 01
// MeshBuffer(5) -> Leaf arbre 01
// MeshBuffer(6) -> Some twigs another tree
// MeshBuffer(7) -> Twigs Arbre 02
// MeshBuffer(8) -> Leaf Arbre 02
// MeshBuffer(9) -> Some twigs another tree
// MeshBuffer(10) -> Quelques rectangles flottant
// MeshBuffer(11) -> Bark
// MeshBuffer(12) -> Twigs
// MeshBuffer(13) -> Mass leaf
ISceneNode *
ElementsModule::generateLargeOakTree(void)
{
    auto raw_mesh = smgr->getMesh(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakTree.obj");
    auto mesh = smgr->getMeshManipulator()->createMeshWithTangents(raw_mesh);

    auto LargeOakTreeNode = this->smgr->addEmptySceneNode();
    LargeOakTreeNode->setName("LargeOakTreeNode");

    irr::scene::SMesh   *barkMesh = new irr::scene::SMesh();
    barkMesh->addMeshBuffer(mesh->getMeshBuffer(11));

    auto LargeOakTreeBarkNode = this->smgr->addMeshSceneNode(barkMesh, LargeOakTreeNode);
    LargeOakTreeBarkNode->setName("LargeOakTreeBarkNode");
    LargeOakTreeBarkNode->setMaterialType(CustomTreeShader::GetMaterialType());
    LargeOakTreeBarkNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakTreeBark_Diffuse.png"));
    LargeOakTreeBarkNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakTreeBark_Normal.png"));

    LargeOakTreeBarkNode->getMaterial(0).BackfaceCulling = false; // TMP

    LargeOakTreeBarkNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    core::aabbox3df aabb;
    aabb = LargeOakTreeBarkNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    LargeOakTreeBarkNode->getMesh()->setBoundingBox(aabb);


    irr::scene::SMesh   *leafMesh = new irr::scene::SMesh();
    leafMesh->addMeshBuffer(mesh->getMeshBuffer(13));

    auto LargeOakTreeLeafNode = this->smgr->addMeshSceneNode(leafMesh, LargeOakTreeNode);
    LargeOakTreeLeafNode->setName("LargeOakTreeLeafNode");
    LargeOakTreeLeafNode->setMaterialType(CustomLeafShader::GetMaterialType());
    LargeOakTreeLeafNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakLeafBunch_Diffuse.png"));
    LargeOakTreeLeafNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakLeafBunch_Normal.png"));
    LargeOakTreeLeafNode->setMaterialTexture(2, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakLeafBunch_Alpha.png"));
    LargeOakTreeLeafNode->getMaterial(0).BackfaceCulling = false;

    LargeOakTreeLeafNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    aabb = LargeOakTreeLeafNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    LargeOakTreeLeafNode->getMesh()->setBoundingBox(aabb);

    irr::scene::SMesh   *twigsMesh = new irr::scene::SMesh();
    twigsMesh->addMeshBuffer(mesh->getMeshBuffer(12));

    auto LargeOakTreeTwigsNode = this->smgr->addMeshSceneNode(twigsMesh, LargeOakTreeNode);
    LargeOakTreeTwigsNode->setName("LargeOakTreeTwigsNode");
    LargeOakTreeTwigsNode->setMaterialType(CustomLeafShader::GetMaterialType());
    LargeOakTreeTwigsNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakTreeTwigs_Diffuse.png"));
    LargeOakTreeTwigsNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakLeafBunch_Normal.png")); // I dont have normals
    LargeOakTreeTwigsNode->setMaterialTexture(2, driver->getTexture(RESOURCES_PATH "/models/Trees/LargeOakTree/LargeOakTreeTwigs_Alpha.png"));
    LargeOakTreeTwigsNode->getMaterial(0).BackfaceCulling = false;

    LargeOakTreeTwigsNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    aabb = LargeOakTreeTwigsNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    LargeOakTreeTwigsNode->getMesh()->setBoundingBox(aabb);
    
    //LargeOakTreeBarkNode->setScale(irr::core::vector3df(2.0f));
    //LargeOakTreeLeafNode->setScale(irr::core::vector3df(2.0f));
    //LargeOakTreeTwigsNode->setScale(irr::core::vector3df(2.0f));
    LargeOakTreeNode->setPosition(irr::core::vector3df(0.0f));
    //LargeOakTreeNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));

    return LargeOakTreeNode;
}

//
// ROOT_NODE
// |-> AmericanMoutainAshNode
//     |-> AmericanMoutainAshBarkNode
//     |-> AmericanMoutainAshLeafNode
//
// MeshBuffer(0) -> Bending Bark
// MeshBuffer(1) -> Bending Leaf
// MeshBuffer(2) -> Leaf
// MeshBuffer(3) -> Bark
ISceneNode *
ElementsModule::generateAmericanMoutainAshTree(void)
{
    auto raw_mesh = smgr->getMesh(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMoutainAsh.obj");
    auto mesh = smgr->getMeshManipulator()->createMeshWithTangents(raw_mesh);

    auto AmericanMoutainAshNode = this->smgr->addEmptySceneNode();
    AmericanMoutainAshNode->setName("AmericanMoutainAshNode");

    irr::scene::SMesh   *barkMesh = new irr::scene::SMesh();
    barkMesh->addMeshBuffer(mesh->getMeshBuffer(3));

    auto AmericanMoutainAshBarkNode = this->smgr->addMeshSceneNode(barkMesh, AmericanMoutainAshNode);
    AmericanMoutainAshBarkNode->setName("AmericanMoutainAshBarkNode");
    AmericanMoutainAshBarkNode->setMaterialType(CustomTreeShader::GetMaterialType());
    AmericanMoutainAshBarkNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMountainAsh_Bark_Diffuse.png"));
    AmericanMoutainAshBarkNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMoutainAsh_Bark_Normal.png"));

    AmericanMoutainAshBarkNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    core::aabbox3df aabb;
    aabb = AmericanMoutainAshBarkNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    AmericanMoutainAshBarkNode->getMesh()->setBoundingBox(aabb);

    irr::scene::SMesh   *needlesMesh = new irr::scene::SMesh();
    needlesMesh->addMeshBuffer(mesh->getMeshBuffer(2));
    auto AmericanMoutainAshLeafNode = this->smgr->addMeshSceneNode(needlesMesh, AmericanMoutainAshNode);
    AmericanMoutainAshLeafNode->setName("AmericanMoutainAshLeafNode");
    AmericanMoutainAshLeafNode->setMaterialType(CustomLeafShader::GetMaterialType());
    AmericanMoutainAshLeafNode->setMaterialTexture(0, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMountainAsh_LeafBunch_Diffuse.png"));
    AmericanMoutainAshLeafNode->setMaterialTexture(1, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMountainAsh_LeafBunch_Normal.png"));
    AmericanMoutainAshLeafNode->setMaterialTexture(2, driver->getTexture(RESOURCES_PATH "/models/Trees/AmericanMoutainAsh/AmericanMountainAsh_LeafBunch_Alpha.png"));
    AmericanMoutainAshLeafNode->getMaterial(0).BackfaceCulling = false;

    AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    //AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(1)->recalculateBoundingBox();
    aabb = AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    //aabb.addInternalBox(AmericanMoutainAshLeafNode->getMesh()->getMeshBuffer(1)->getBoundingBox());
    AmericanMoutainAshLeafNode->getMesh()->setBoundingBox(aabb);

    AmericanMoutainAshNode->setPosition(irr::core::vector3df(0.0f));
    AmericanMoutainAshNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));

    return AmericanMoutainAshNode;
}

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
ISceneNode *
ElementsModule::generateDouglasFirTree(void)
{
    auto raw_mesh = smgr->getMesh(RESOURCES_PATH "/models/Trees/DouglasFir/HEO_DouglasFir.obj");
    auto mesh = smgr->getMeshManipulator()->createMeshWithTangents(raw_mesh);

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

    DouglasFirBarkNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    DouglasFirBarkNode->getMesh()->getMeshBuffer(1)->recalculateBoundingBox();
    core::aabbox3df aabb;
    aabb = DouglasFirBarkNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    aabb.addInternalBox(DouglasFirBarkNode->getMesh()->getMeshBuffer(1)->getBoundingBox());
    DouglasFirBarkNode->getMesh()->setBoundingBox(aabb);

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
    DouglasFirNeedlesNode->getMaterial(0).BackfaceCulling = false;
    DouglasFirNeedlesNode->getMaterial(1).BackfaceCulling = false;

    // Settings not needed at the end.

    DouglasFirNeedlesNode->getMesh()->getMeshBuffer(0)->recalculateBoundingBox();
    DouglasFirNeedlesNode->getMesh()->getMeshBuffer(1)->recalculateBoundingBox();
    aabb = DouglasFirNeedlesNode->getMesh()->getMeshBuffer(0)->getBoundingBox();
    aabb.addInternalBox(DouglasFirNeedlesNode->getMesh()->getMeshBuffer(1)->getBoundingBox());
    DouglasFirNeedlesNode->getMesh()->setBoundingBox(aabb);

    DouglasFirNode->setPosition(irr::core::vector3df(0.0f));
    DouglasFirNode->setRotation(irr::core::vector3df(-90.0f, 0.0f, 0.0f));

    return DouglasFirNode;

    //std::cout << "DouglasFir absolute position : (" << DouglasFirNode->getAbsolutePosition().X << ", " << DouglasFirNode->getAbsolutePosition().Y << ", " << DouglasFirNode->getAbsolutePosition().Z << ")" << std::endl;
    //std::cout << "DouglasFir position : (" << DouglasFirNode->getPosition().X << ", " << DouglasFirNode->getPosition().Y << ", " << DouglasFirNode->getPosition().Z << ")" << std::endl;
    //std::cout << "DouglasFir scale : (" << DouglasFirNode->getScale().X << ", " << DouglasFirNode->getScale().Y << ", " << DouglasFirNode->getScale().Z << ")" << std::endl;
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
