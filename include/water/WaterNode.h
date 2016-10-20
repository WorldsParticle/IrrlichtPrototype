#include <irrlicht.h>

using namespace irr;

class WaterShader;
class WaterFrameBuffers;

class WaterNode : public scene::ISceneNode
{
public:
  WaterNode(scene::ISceneNode *parent, scene::ISceneManager *smgr, const core::vector3df &pos, const core::vector2df &size);
  ~WaterNode();

  inline ISceneNode *waterNode()
  { return _waterNode; }

  void init();

  virtual void                          OnRegisterSceneNode();
  virtual void                          OnAnimate(u32 timeMs);
  virtual void                          render();
  virtual const core::aabbox3d<float>&  getBoundingBox() const;

private:

  void  applyReflection();
  void  applyRefraction();

  static const core::vector2df  TILE_SIZE;

  scene::ISceneManager  *_smgr;

  const core::vector3df _pos; // Center
  const core::vector2df _size;

  scene::IMesh          *_waterMesh;
  scene::ISceneNode     *_waterNode;

  WaterShader           *_waterShader;
  WaterFrameBuffers     *_waterBuffers;

  scene::ICameraSceneNode *_reflectionCamera;

  u32                   _time;

};
