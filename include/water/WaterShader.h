#include <irrlicht.h>
#include <iostream>

#include "Configuration.h"

using namespace irr;

class WaterShader : public video::IShaderConstantSetCallBack
{
public:

  WaterShader(scene::ISceneManager *smgr);
  ~WaterShader();

  void init();

  virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData);

  inline s32  material()
  { return _material; }

private:

 const static core::stringc VERTEX_FILE;
 const static core::stringc FRAGMENT_FILE;

 scene::ISceneManager *_smgr;

 s32                  _material;

};
