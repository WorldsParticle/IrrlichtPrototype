#include "scene/water/WaterFrameBuffers.h"
#include <iostream>


const core::stringc WaterFrameBuffers::DUDV_FILE = RESOURCES_PATH "/waterDUDV.png";
const core::stringc WaterFrameBuffers::NORMAL_FILE = RESOURCES_PATH "/normalMap.png";


WaterFrameBuffers::WaterFrameBuffers(scene::ISceneManager *smgr) :
  _reflectionFrameBuffer(nullptr),
  _reflectionTexture(nullptr),
  _reflectionDepth(nullptr),
  _refractionFrameBuffer(nullptr),
  _refractionTexture(nullptr),
  _refractionDepth(nullptr),
  _dudvMap(nullptr),
  _normalMap(nullptr),
  _smgr(smgr)
{
  init();
}

WaterFrameBuffers::~WaterFrameBuffers()
{
  // drop and stuff
}

void WaterFrameBuffers::init()
{
  video::IVideoDriver *driver = _smgr->getVideoDriver();

  _reflectionTexture = driver->addRenderTargetTexture(
    core::dimension2du(REFLECTION_WIDTH, REFLECTION_HEIGHT)); // noms trop longs ..

  _refractionTexture = driver->addRenderTargetTexture(
    core::dimension2du(REFRACTION_WIDTH, REFRACTION_HEIGHT));

  // peut être faire une table.. plus lisbile
  _dudvMap = driver->getTexture(DUDV_FILE);
  _normalMap = driver->getTexture(NORMAL_FILE);
  //_refractionDepth = driver->getTexture(DEPTH_FILE)

}
