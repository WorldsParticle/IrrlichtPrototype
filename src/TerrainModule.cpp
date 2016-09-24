#include "TerrainModule.h"
#include "bitmap/bitmap_image.hpp"
#include "noise/simplexnoise.hpp"

int TerrainModule::init()
{
	// add terrain scene node
	_terrain = smgr->addTerrainSceneNode(
		"./ressources/terrain-heightmap.bmp",
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

	_terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	_terrain->setMaterialTexture(0,
		driver->getTexture("./ressources/terrain-texture.jpg"));
	_terrain->setMaterialTexture(1,
		driver->getTexture("./ressources/detailmap3.jpg"));

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
	return 0;
}

int TerrainModule::update()
{
	//nothing to do
	return 0;
}

f32 TerrainModule::getHeight(f32 x, f32 y) const
{
    return _terrain->getHeight(x, y);
}

void TerrainModule::setHeightmap()
{
    io::path p(_path.c_str());
	IReadFile * f = device->getFileSystem()->createAndOpenFile(p);
    _terrain->setScale(core::vector3df(750.0f, 125.4f, 750.0f));
    _terrain->loadHeightMap(f);
    camera->removeAnimator(_anim);

    _terrain->setMaterialFlag(video::EMF_LIGHTING, false);

    _terrain->setMaterialTexture(0,
        driver->getTexture("./ressources/terrain-texture.jpg"));
    _terrain->setMaterialTexture(1,
        driver->getTexture("./ressources/detailmap3.jpg"));

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

        _path = "tmp.bmp";
		_heightmapImage->save_image(_path);
		_heightmapImage->clear();
		//delete(_heightmapImage);
        delete(tab);
}
