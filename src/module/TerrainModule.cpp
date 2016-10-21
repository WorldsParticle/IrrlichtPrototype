#include "module/TerrainModule.h"
#include "Configuration.h"

#include "tool/bitmap_image.h"
#include "tool/simplexnoise.h"

#include "generator/generator.h"
#include "map/map.h"

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
	// add terrain scene node
	/*_terrain = smgr->addTerrainSceneNode(
        RESOURCES_PATH "/terrain-heightmap.bmp",
		0,                  // parent node
		-1,                 // node id
		core::vector3df(0.f, 0.f, 0.f),     // position
		core::vector3df(0.f, 0.f, 0.f),     // rotation
        core::vector3df(40.f, 4.4f, 40.f),  // scale
		video::SColor(255, 255, 255, 255),   // vertexColor
		5,                  // maxLOD
		scene::ETPS_17,             // patchSize
		4                   // smoothFactor
		);

	_terrain->setMaterialFlag(video::EMF_LIGHTING, true);

	_terrain->setMaterialTexture(0,
		driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
	_terrain->setMaterialTexture(1,
		driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));

	_terrain->setMaterialType(video::EMT_DETAIL_MAP);

	_terrain->scaleTexture(1.0f, 20.0f);


	// create triangle selector for the terrain
	scene::ITriangleSelector* selector
		= smgr->createTerrainTriangleSelector(_terrain, 0);
	_terrain->setTriangleSelector(selector);

	// create collision response animator and attach it to the camera
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, camera, core::vector3df(60, 100, 60),
		core::vector3df(0, 0, 0),
		core::vector3df(0, 50, 0));
	selector->drop();
	camera->addAnimator(anim);
    _anim = anim;
	anim->drop();*/
	return 0;
}

int TerrainModule::update()
{
	return 0;
}

void TerrainModule::generateFromMap(::map::MapGraph *mapGraph)
{
	clearNodes();
	float scale = 100.f; // temp
	_terrainGridNodes.resize(mapGraph->gridXMax() * mapGraph->gridYMax());
	_terrainGridAnims.resize(mapGraph->gridXMax() * mapGraph->gridYMax());

	for (unsigned int x = 0; x < mapGraph->gridXMax(); ++x)
		for (unsigned int y = 0; y < mapGraph->gridYMax(); ++y)
		{
			std::cout << "x : " << x << ", y : " << y << std::endl;
			scene::ITerrainSceneNode *terrain = smgr->addTerrainSceneNode(
																					mapGraph->heightmapAt(mapGraph->gridYMax() - y - 1, x).c_str(),
																					0,
																					-1,                 // node id
																					core::vector3df(y * mapGraph->gridSize() * scale, 0.f, x * mapGraph->gridSize() * scale),     // position
																					core::vector3df(0.f, 0.f, 0.f),     // rotation
																			    core::vector3df(scale, scale, scale),  // scale
																					video::SColor(255, 255, 255, 255),   // vertexColor
																					5,                  // maxLOD
																					scene::ETPS_17,             // patchSize
																					4); // smoothFactor
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

/*
void TerrainModule::generate(int size, int seed){
	_heightmapImage = new bitmap_image(size, size);
    float *tab = new float[size * size];
    float min = 1.0f, max = -1.0f;
    float fseed = static_cast<float>(seed) / 100000.0f;

    // generate noise values
    for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
    {

        float noise = octave_noise_3d(12, 1.0f, 0.00075f, static_cast<float>(j) / 100.0f, static_cast<float>(i) / 100.0f, fseed);

        if (noise < min)
            min = noise;
        if (noise > max)
            max = noise;
        tab[i * size + j] = noise;
    }

    // normalize to range [0, 1];
    float diff = max - min;
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
        {
                    tab[i * size + j] = (tab[i * size + j] - min) / diff;
                    //if (i == 0)
                    //    std::cout << tab[i * size + j];

         //clamp for floor.
            if (tab[i * size + j] < 0.38f)
                tab[i * size + j] = 0.38f * 0.8f+ tab[i * size + j] * 0.2f;
            tab[i * size + j] -= 0.38f * 0.8f;
        }

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            float point = tab[i * size + j];
            int color = (int)(point * 255.0);

			_heightmapImage->set_pixel(j, i, color, color, color);
        }

        _path = (std::string)RESOURCES_PATH + "/tmp.bmp";
		_heightmapImage->save_image(_path);
		_heightmapImage->clear();
        //delete(_heightmapImage);
        delete(tab);
}

void TerrainModule::generateVoronoi(){
    std::cout << "Starting generating VORONOI." << std::endl;
    gen::Generator gen;

    ::map::MapGraph  *map = new ::map::MapGraph(512,
                                            512, 2048);

    gen.run(map);
    _path = (std::string)RESOURCES_PATH + "/mapheight.bmp";
    std::cout << "Finished generating VORONOI." << std::endl;
}

void TerrainModule::generateRadial(int size, int seed){
    _heightmapImage = new bitmap_image(size, size);
    float *tab = new float[size * size];
    float min = 1.0f, max = -1.0f;
    float fseed = static_cast<float>(seed) / 100000.0f;

    // generate noise values
    for (int i = 0; i < size; ++i)
    for (int j = 0; j < size; ++j)
    {

        float noise = octave_noise_3d(12, 1.0f, 0.00075f, static_cast<float>(j) / 100.0f, static_cast<float>(i) / 100.0f, fseed);

        if (noise < min)
            min = noise;
        if (noise > max)
            max = noise;
        tab[i * size + j] = noise;
    }

    // normalize to range [0, 1];
    float diff = max - min;
            for (int i = 0; i < size; ++i)
                for (int j = 0; j < size; ++j)
        {
                    tab[i * size + j] = (tab[i * size + j] - min) / diff;
        }

    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
        {
            float point = tab[i * size + j];
            float dx = (2 * (float)j) / (float)size - 1;
            float dy = (2 * (float)i) / (float)size - 1;
            float d = sqrt(dx * dx + dy * dy);
            int color;
            if (point > (0.75 * 0.89 * d * d))
                color = 255.0;
            else
                color = 0;

            _heightmapImage->set_pixel(j, i, color, color, color);
        }

        _path = (std::string)RESOURCES_PATH + "/radialtmp.bmp";
        _heightmapImage->save_image(_path);
        _heightmapImage->clear();
        delete(_heightmapImage);
        delete(tab);
}

void TerrainModule::setHeightmap()
{
    io::path p(_path.c_str());
	IReadFile * f = device->getFileSystem()->createAndOpenFile(p);
    _terrain->setScale(core::vector3df(25.0f, 10.0f, 25.0f));
    _terrain->loadHeightMap(f);
    camera->removeAnimator(_anim);

    _terrain->setMaterialFlag(video::EMF_LIGHTING, true);

    _terrain->setMaterialTexture(0,
		driver->getTexture(RESOURCES_PATH "/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1,
		driver->getTexture(RESOURCES_PATH "/detailmap3.jpg"));

    _terrain->setMaterialType(video::EMT_DETAIL_MAP);

    _terrain->scaleTexture(1.0f, 20.0f);


    // create triangle selector for the terrain
    scene::ITriangleSelector* selector
        = smgr->createTerrainTriangleSelector(_terrain, 0);
    _terrain->setTriangleSelector(selector);

    // create collision response animator and attach it to the camera
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, camera, core::vector3df(60, 100, 60),
        core::vector3df(0, 0, 0),
        core::vector3df(0, 50, 0));
    selector->drop();
    camera->addAnimator(anim);
    _anim = anim;
    anim->drop();

}
*/

void TerrainModule::clearNodes()
{
	for (scene::ITerrainSceneNode *node : _terrainGridNodes)
		delete node;
	for (scene::ISceneNodeAnimator *anim : _terrainGridAnims)
		delete anim;
}
