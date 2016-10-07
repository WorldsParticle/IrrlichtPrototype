#include "water/WaterFrameBuffers.h"
#include <iostream>


const core::stringc WaterFrameBuffers::DUDV_FILE = RESOURCES_PATH "/waterDUDV.png";

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
    core::dimension2du(REFLECTION_WIDTH, REFLECTION_HEIGHT));
  _refractionTexture = driver->addRenderTargetTexture(
    core::dimension2du(REFRACTION_WIDTH, REFRACTION_HEIGHT));
  _dudvMap = driver->getTexture(DUDV_FILE);
}
