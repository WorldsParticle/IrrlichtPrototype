#include "module/TerrainModule.h"
#include "Configuration.h"
#include "Core.h"

#include "tool/bitmap_image.h"
#include "tool/simplexnoise.h"

#include "generator/generator.h"
#include "map/map.h"

#include "scene/terrain/TerrainSceneNode.h"

TerrainModule::TerrainModule(Core *c, IrrlichtDevice* _device, scene::ICameraSceneNode* _camera) :
	AModule(c, _device, _camera),
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
	//TerrainSceneNode *n = new TerrainSceneNode(nullptr, nullptr, nullptr, -1);
	//TerrainSceneNode *terrain = new TerrainSceneNode(
	//	smgr->getRootSceneNode(),
	//	smgr,
	//	smgr->getFileSystem(),
	//	-1, // Id
	//	8, // maxLOD
	//	scene::ETPS_17,
	//	core::vector3df(0.f, 0.f, 0.f), // position
	//	core::vector3df(0.f, 0.f, 0.f), // rotation
	//	core::vector3df(MAP_SIZE, 0, MAP_SIZE) // scale
	//);

	//terrain->setMaterialFlag(video::EMF_LIGHTING, true);
	//terrain->setMaterialTexture(0,
	//	driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
	//terrain->setMaterialTexture(1,
	//	driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));
	//terrain->setMaterialType(video::EMT_DETAIL_MAP);
	//terrain->scaleTexture(1.0f, 20.0f);

	// add terrain scene node
	//scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
	//	RESOURCES_PATH "/terrain-heightmap.bmp",
	//	0,                  // parent node
	//	-1,                 // node id
	//	-ORIGIN_POS,     // position
	//	core::vector3df(0.f, 0.f, 0.f),     // rotation
	//	core::vector3df(MAP_SIZE, 4.4f, MAP_SIZE),  // scale
	//	video::SColor(255, 255, 255, 255),   // vertexColor
	//	5,                  // maxLOD
	//	scene::ETPS_17,             // patchSize
	//	4                   // smoothFactor
	//);

	//terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	//terrain->setMaterialTexture(0,
	//	driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
	//terrain->setMaterialTexture(1,
	//	driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));

	//terrain->setMaterialType(video::EMT_DETAIL_MAP);

	//terrain->scaleTexture(1.0f, 20.0f);

	//terrain->drop();
	//delete n;
	return 0;
}

int TerrainModule::update()
{
	return 0;
}

void TerrainModule::generateFromMap(::map::MapGraph &map)
{
    clearNodes();
	float scale = WORLD_UNIT_SCALE;
    _terrainGridNodes.resize(map.gridXMax() * map.gridZMax());
    _terrainGridAnims.resize(map.gridXMax() * map.gridZMax());

    for (unsigned int x = 0; x < map.gridXMax(); ++x)
    {
        for (unsigned int z = 0; z < map.gridZMax(); ++z)
        {
            std::cout << "x : " << x << ", z : " << z << std::endl;
						scene::ITerrainSceneNode *terrain = loadTerrain(map, x, z, scale);

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

            _terrainGridNodes[x + map.gridXMax() * z] = terrain;
            _terrainGridAnims[x + map.gridXMax() * z] = anim;
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

scene::ITerrainSceneNode	*TerrainModule::loadTerrain(::map::MapGraph &map, unsigned int x, unsigned int z, float scale)
{
	TerrainSceneNode *terrain = new TerrainSceneNode(
			smgr->getRootSceneNode(),
			smgr,
			smgr->getFileSystem(),
			-1, // Id
			8, // maxLOD
			scene::ETPS_17,
			core::vector3df(z * map.tileSize() * scale, 0.f, x * map.tileSize() * scale), // position
			core::vector3df(0.f, 0.f, 0.f), // rotation
			core::vector3df(scale, scale, scale) // scale
		);

	io::IReadFile* file = smgr->getFileSystem()->createAndOpenFile(map.heightmapAt(map.gridZMax() - z - 1, x).c_str());
	terrain->loadHeightMap(
												file,
												video::SColor(255, 255, 255, 255), // vertexColor)
												5); // smoothFactor
	if (file)
		file->drop();

	///
	/// LMP - Part of placing the terrain at the good position.
	/// Previous position set was not working at all.
	///

	const auto &aabb = terrain->getBoundingBox();
	terrain->setPosition(irr::core::vector3df(z * (aabb.MaxEdge.X - aabb.MinEdge.X), 0.0f, x * (aabb.MaxEdge.Z - aabb.MinEdge.Z)));

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

	terrain->drop();

	return terrain;
}

/*
void test_tmp()
{
   m_fTrackScale = track_scale;
   video::ITexture* detail = driver->getTexture("terrain/detail.bmp");

//Open up the big heighmap and big texture
   video::IImage* heightMap = smgr->getVideoDriver()->createImageFromFile("terrain/island/terrain/heightmap.bmp");
   video::IImage* bigTex = smgr->getVideoDriver()->createImageFromFile("terrain/island/terrain/tex.bmp");
   s32 data[129*129];

//Split it up into 8x8 tiles
   for(int tile=0;tile<64;tile++){

//Sub will be a 129x129 tile of the heightmap
      video::IImage* sub = driver->createImageFromData(video::ECF_A8R8G8B8,core::dimension2di(129,129),&data);

//Create a 256x256 texture and copy the appropriate portion of the big texture to it.
      video::ITexture *txt = driver->addTexture(core::dimension2d<s32>(256,256), "texture", video::ECF_A8R8G8B8);
      video::SColor *p = (video::SColor*)txt->lock();

      for(u32 j=0; j<txt->getSize().Height; j++)
       for(u32 i=0; i<txt->getSize().Width; i++)
         p[j * txt->getSize().Width + i] = bigTex->getPixel(256*(tile%8) + i,256*(tile/8)+j);
      txt->unlock();

      txt->regenerateMipMapLevels();

//Now copy the correct portion of the large heightmap to the tile
      sub->lock();
      for(int i=0;i < 129;i++)
         for(int j=0; j < 129 ; j++)
            sub->setPixel(i,j,heightMap->getPixel(i + (128 * (tile %8)),j + (128 * (tile/8))));
      sub->unlock();

//I split the engine a little bit so you can make a terrainscenenode from an image
      node[tile] = smgr->addTerrainSceneNode(sub,0,-1,core::vector3df(0.0,0.0,0.0),core::vector3df(0.0,0.0,0.0),core::vector3df(1.0,1.0,1.0),video::SColor(255,255,255,255),5,scene::ETPS_17,5,false);

//Add the texture
      node[tile]->setMaterialFlag(video::EMF_LIGHTING, false);
      node[tile]->setMaterialTexture(0,txt);
      //node[tile]->setMaterialTexture(1,detail);
      node[tile]->setMaterialType(video::EMT_DETAIL_MAP);
      node[tile]->setScale(core::vector3df(track_scale,track_scale,track_scale));
      node[tile]->setPosition(core::vector3df(128.0f * (tile%8)*track_scale,0.0f,128.0f * (tile/8)*track_scale));
      node[tile]->scaleTexture(1.0,64.0);
   }

//This function takes the adjacent tiles and stitches the edges together.
//Theoretically this should be unnecessary but the smoothing algorithm can cause slight differences at the edges.
   for(int i=0; i<7;i++)
      for(int j=0; j<7; j++)
      {
         StitchHeightmap(node[i*8 + j],node[i*8 + j + 1],0);
         StitchHeightmap(node[i*8 + j],node[(i+1)*8 + j],1);
      }

   return true;
}*/
