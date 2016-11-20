#include <iostream>

#include "scene/water/WaterNode.h"
#include "Configuration.h"

#include "scene/water/WaterFrameBuffers.h"
#include "scene/water/WaterShader.h"

#include "WorldSettings.h"

const core::vector2df  WaterNode::TILE_SIZE = core::vector2df(WP_SEA_TILE_SIZE, WP_SEA_TILE_SIZE);


WaterNode::WaterNode(scene::ISceneNode *parent, scene::ISceneManager *smgr, const core::vector3df &pos, const core::vector2df &size) :
  scene::ISceneNode(parent, smgr),
  _smgr(smgr),
  _pos(pos),
  _size(size),
  _waterMesh(nullptr),
  _waterNode(nullptr),
  _waterShader(nullptr),
  _waterBuffers(nullptr),
  _reflectionCamera(nullptr),
  _time(0)
{
  init();
}

void WaterNode::init()
{
  _reflectionCamera = _smgr->addCameraSceneNode(0, core::vector3df(0, 0, 0), core::vector3df(0, 0, 0), -1, false);
  _reflectionCamera->bindTargetAndRotation(true);

  _waterShader = new WaterShader(_smgr, &_time);
  _waterBuffers = new WaterFrameBuffers(_smgr);

  _waterMesh = _smgr->getGeometryCreator()->createPlaneMesh(TILE_SIZE,
                      core::dimension2du(_size.X / TILE_SIZE.X, _size.Y / TILE_SIZE.Y),
                      0,
                      core::dimension2df(4096 / 512, 4096 / 512));

  _waterNode = _smgr->addMeshSceneNode(_waterMesh);
  //_waterNode = _smgr->addWaterSurfaceSceneNode(_waterMesh, 5.0f, 500.0f, 200.0f);
  _waterNode->setPosition(_pos);


  _waterNode->setMaterialType((video::E_MATERIAL_TYPE)_waterShader->material());

  _waterNode->setMaterialTexture(0, _waterBuffers->reflectionTexture());
  _waterNode->setMaterialTexture(1, _waterBuffers->refractionTexture());
  _waterNode->setMaterialTexture(2, _waterBuffers->dudvMap());
  _waterNode->setMaterialTexture(3, _waterBuffers->normalMap());
}

WaterNode::~WaterNode()
{

}

void WaterNode::OnAnimate(u32 timeMS)
{
  ISceneNode::OnAnimate(timeMS);

  _time = timeMS;

  if (IsVisible)
  {
    setVisible(false);

    applyReflection();
    applyRefraction();

    setVisible(true);
  }
}

void WaterNode::OnRegisterSceneNode()
{
  if (IsVisible)
	{
		_smgr->registerNodeForRendering(this);
	}

  ISceneNode::OnRegisterSceneNode();
}


void WaterNode::render()
{
  // not usefull
}

const core::aabbox3d<float>& WaterNode::getBoundingBox() const
{
  return _waterMesh->getBoundingBox();
}

void WaterNode::applyReflection()
{
  _smgr->getVideoDriver()->setRenderTarget(_waterBuffers->reflectionTexture(), true, true);

  scene::ICameraSceneNode *currentCamera = _smgr->getActiveCamera();
  _reflectionCamera->setFarValue(currentCamera->getFarValue());
  _reflectionCamera->setFOV(currentCamera->getFOV());

  core::vector3df position = currentCamera->getAbsolutePosition();
  position.Y = -position.Y + 2 * _pos.Y;
  _reflectionCamera->setPosition(position);

  core::vector3df target = currentCamera->getTarget();
  target.Y = -target.Y + 2 * _pos.Y;
  _reflectionCamera->setTarget(target);

  _smgr->setActiveCamera(_reflectionCamera);

  core::plane3d<f32>  reflectionclipPlane(_pos.X, _pos.Y, _pos.Z, 0, 1, 0);
  _smgr->getVideoDriver()->setClipPlane(0, reflectionclipPlane, true);

  _smgr->drawAll();

  _smgr->getVideoDriver()->enableClipPlane(0, false);
  _smgr->getVideoDriver()->setRenderTarget(0);
  _smgr->setActiveCamera(currentCamera);

}

void WaterNode::applyRefraction()
{
  _smgr->getVideoDriver()->setRenderTarget(_waterBuffers->refractionTexture(), true, true);

  core::plane3d<f32>  refractionclipPlane(_pos.X, _pos.Y, _pos.Z, 0, -1, 0);
  _smgr->getVideoDriver()->setClipPlane(0, refractionclipPlane, true);

  _smgr->drawAll();

  _smgr->getVideoDriver()->enableClipPlane(0, false);
  _smgr->getVideoDriver()->setRenderTarget(0);
}
