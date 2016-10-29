#include "module/TerrainModule.h"
#include "Configuration.h"

#include "tool/bitmap_image.h"
#include "tool/simplexnoise.h"

#include "generator/generator.h"
#include "map/map.h"

#include "scene/terrain/TerrainSceneNode.h"

TerrainModule::TerrainModule(IrrlichtDevice* _device, scene::ICameraSceneNode* _camera) :
	AModule(_device, _camera),
	_terrainGridNodes(),
	_terrainGridAnims()
{

}

TerrainModule::~TerrainModule()
{
	clearNodes();
}

int TerrainModule::init()
{
	TerrainSceneNode *n = new TerrainSceneNode(nullptr, nullptr, nullptr, -1);
	delete n;
	return 0;
}

int TerrainModule::update()
{
	return 0;
}

void TerrainModule::generateFromMap(::map::MapGraph *mapGraph)
{
    clearNodes();
    float scale = 500.0f; // temp
    _terrainGridNodes.resize(mapGraph->gridXMax() * mapGraph->gridYMax());
    _terrainGridAnims.resize(mapGraph->gridXMax() * mapGraph->gridYMax());

    for (unsigned int x = 0; x < mapGraph->gridXMax(); ++x)
    {
        for (unsigned int y = 0; y < mapGraph->gridYMax(); ++y)
        {
            std::cout << "x : " << x << ", y : " << y << std::endl;
						TerrainSceneNode *terrain = new TerrainSceneNode(
								smgr->getRootSceneNode(),
								smgr,
								smgr->getFileSystem(),
								-1, // Id
								8, // maxLOD
								scene::ETPS_17,
								core::vector3df(y * mapGraph->gridSize() * scale, 0.f, x * mapGraph->gridSize() * scale), // position
								core::vector3df(0.f, 0.f, 0.f), // rotation
                core::vector3df(scale, scale, scale) // scale
							);
						io::IReadFile* file = smgr->getFileSystem()->createAndOpenFile(mapGraph->heightmapAt(mapGraph->gridYMax() - y - 1, x).c_str());
						terrain->loadHeightMap(
																	file,
																	video::SColor(255, 255, 255, 255), // vertexColor)
																	4); // smoothFactor
						if (file)
							file->drop();
						terrain->drop();

            ///
            /// LMP - Part of placing the terrain at the good position.
            /// Previous position set was not working at all.
            ///

            const auto &aabb = terrain->getBoundingBox();
            terrain->setPosition(irr::core::vector3df(y * (aabb.MaxEdge.X - aabb.MinEdge.X), 0.0f, x * (aabb.MaxEdge.Z - aabb.MinEdge.Z)));

            ///
            /// END - LMP - Part of placing the terrain at the good position.
            ///

            terrain->setMaterialFlag(video::EMF_LIGHTING, true);
            terrain->setMaterialTexture(0,
                driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
            terrain->setMaterialTexture(1,
                driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));
            terrain->setMaterialType(video::EMT_DETAIL_MAP);
            terrain->scaleTexture(1.0f, 20.0f);

            // create triangle selector for the terrain
            scene::ITriangleSelector* selector
                = smgr->createTerrainTriangleSelector(terrain, 0);
            terrain->setTriangleSelector(selector);

            // create collision response animator and attach it to the camera
            scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
                selector, camera, core::vector3df(60, 100, 60),
                core::vector3df(0, 0, 0),
                core::vector3df(0, 50, 0));
            selector->drop();
            camera->addAnimator(anim);

            _terrainGridNodes[x + mapGraph->gridXMax() * y] = terrain;
            _terrainGridAnims[x + mapGraph->gridXMax() * y] = anim;
        }
    }
}

void TerrainModule::clearNodes()
{
    for (scene::ITerrainSceneNode *node : _terrainGridNodes)
        delete node;
    for (scene::ISceneNodeAnimator *anim : _terrainGridAnims)
        delete anim;
}

float
TerrainModule::getHeight(irr::f32 x, irr::f32 z)
{
    for (scene::ITerrainSceneNode *terrainSceneNode : this->_terrainGridNodes)
    {
        irr::f32 height = terrainSceneNode->getHeight(x, z);
        if (height != -FLT_MAX)
            return height;
    }
    return -FLT_MAX;
}
