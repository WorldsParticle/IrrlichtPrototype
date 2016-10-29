#include "scene/water/WaterShader.h"
#include "Configuration.h"

#include "module/SkyboxModule.h" // Temporary .. or not ?

const core::stringc WaterShader::VERTEX_FILE = RESOURCES_PATH "/shaders/watVertTemp.txt";
const core::stringc WaterShader::FRAGMENT_FILE = RESOURCES_PATH "/shaders/watFragTemp.txt";


WaterShader::WaterShader(scene::ISceneManager *smgr, const u32 *time) :
  _smgr(smgr),
  _material(-1),
  _time(time)
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


void WaterShader::OnSetConstants(video::IMaterialRendererServices *services, s32)
{
  // the following 5 next lignes are static and waiting to have a proper dynamique structure to use :)
  // they are still 4 hardcoded attribute in shader waiting to be in here

  float moveFactor = 0.02f * (*_time); // arbritary, wave speed, to catch from climat
  moveFactor = (int)moveFactor % 1000;
  moveFactor /= 1000.0f;

  core::vector3df lightColour(0.95, 0.95, 0.9); // ca fait l'affaire
  core::vector3df lightPosition(20000, 20000, -20000); // inverser x/z pour nuit

  // end of static madness

  video::IVideoDriver *driver = services->getVideoDriver();

  core::matrix4 projection = driver->getTransform(video::ETS_PROJECTION);
	core::matrix4 view = driver->getTransform(video::ETS_VIEW);
	core::matrix4 world = driver->getTransform(video::ETS_WORLD); // use as model ?
  core::vector3df camPos = _smgr->getActiveCamera()->getAbsolutePosition();

  services->setVertexShaderConstant("projectionMatrix", projection.pointer(), 16);
	services->setVertexShaderConstant("viewMatrix", view.pointer(), 16);
	services->setVertexShaderConstant("modelMatrix", world.pointer(), 16);
  services->setVertexShaderConstant("camPos", &camPos.X, 3);
  services->setVertexShaderConstant("lightPosition", &lightPosition.X, 3);
  services->setPixelShaderConstant("lightColour", &lightColour.X, 3); // static
  services->setPixelShaderConstant("moveFactor", &moveFactor, 1); // static

  int var0 = 0; // refraction
  int var1 = 1; // reflection
  int var2 = 2; // dudvMap
  int var3 = 3; // normalMap

  services->setPixelShaderConstant("reflectionTexture", &var0, 1);
  services->setPixelShaderConstant("refractionTexture", &var1, 1);
  services->setPixelShaderConstant("dudvMap", &var2, 1);
  services->setPixelShaderConstant("normalMap", &var3, 1);
}
