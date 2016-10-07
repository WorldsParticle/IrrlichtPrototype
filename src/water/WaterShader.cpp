#include "water/WaterShader.h"
#include "Configuration.h"

const core::stringc WaterShader::VERTEX_FILE = RESOURCES_PATH "/shaders/watVertTemp.txt";
const core::stringc WaterShader::FRAGMENT_FILE = RESOURCES_PATH "/shaders/watFragTemp.txt";


WaterShader::WaterShader(scene::ISceneManager *smgr) :
  _smgr(smgr),
  _material(-1)
{
  init();
}

WaterShader::~WaterShader()
{
  // To do
}

void WaterShader::init()
{
  video::IGPUProgrammingServices *GPU = _smgr->getVideoDriver()->getGPUProgrammingServices();

  core::stringc fragmentShader = FRAGMENT_FILE;
  core::stringc vertexShader = VERTEX_FILE;
  _material = GPU->addHighLevelShaderMaterialFromFiles(
		          vertexShader.c_str(), "main", video::EVST_VS_1_1,
		          fragmentShader.c_str(), "main", video::EPST_PS_1_1,
		          this,
              video::EMT_TRANSPARENT_REFLECTION_2_LAYER);
}


void WaterShader::OnSetConstants(video::IMaterialRendererServices *services, s32 userData)
{

  video::IVideoDriver *driver = services->getVideoDriver();

  core::matrix4 projection = driver->getTransform(video::ETS_PROJECTION);
	core::matrix4 view = driver->getTransform(video::ETS_VIEW);
	core::matrix4 world = driver->getTransform(video::ETS_WORLD); // use as model ?

  services->setVertexShaderConstant("projectionMatrix", projection.pointer(), 16);
	services->setVertexShaderConstant("viewMatrix", view.pointer(), 16);
	services->setVertexShaderConstant("modelMatrix", world.pointer(), 16);
	//services->setVertexShaderConstant("position", &cameraPosition.X, 3);

  int var0 = 0; // refraction
  int var1 = 1; // reflection
  //int var2 = 2; // dudvMap

  services->setPixelShaderConstant("reflectionTexture", &var0, 1);
  services->setPixelShaderConstant("refractionTexture", &var1, 1);
  //services->setPixelShaderConstant("dudvMap", &var2, 1);
}
