#include "module/SkyboxModule.h"
#include "Configuration.h"

#define     TIME_OF_DAY         DAY_LENGTH * 60 * 1000  // Time of one day in ms depending on DAY_LENGTH
#define     TWILIGHT_START      TIME_OF_DAY * 0.5f
#define     NIGHT_START         TIME_OF_DAY * 0.575f
#define     DAWN_START          TIME_OF_DAY * 0.925f

int SkyboxModule::init()
{
    // Init shader for Day/Night cycle
    video::IGPUProgrammingServices* GPUProgrammingServices = driver->getGPUProgrammingServices();
    _shader = GPUProgrammingServices->addHighLevelShaderMaterialFromFiles(
        RESOURCES_PATH "/shaders/skybox_vs.glsl", "main", video::EVST_VS_1_1,
        RESOURCES_PATH "/shaders/skybox_fs.glsl", "main", video::EPST_PS_1_1,
        this);

    // Create all pair Day/Night Skyboxes for all weathers
    createSkyboxesPair(AWeather::E_WEATHER::NONE, "/Day/day", "/Night/night");
    createSkyboxesPair(AWeather::E_WEATHER::RAIN, "/Rain_Day/rainDay", "/Rain_Night/rainNight");
    createSkyboxesPair(AWeather::E_WEATHER::SNOW, "/Snow_Day/snowDay", "/Snow_Night/snowNight");

    // Set current active Skybox
    _active = _skyboxes[_weather].first;
    _active->setVisible(true);

	return 0;
}


void SkyboxModule::createSkyboxesPair(AWeather::E_WEATHER w, const std::string & pathDay, const std::string & pathNight)
{
    // Create Day and Night Skybox
    scene::ISceneNode * day = createSkybox(pathDay);
    scene::ISceneNode * night = createSkybox(pathNight);

    // Create new Texture layer with the opposite time(Day/Night) Skybox.
    // Used by the shader to mix Day & Night Skybox depending on the time
    // Would be easier if irrlicht supported CubeMapping...
    for (u32 i = 0; i < day->getMaterialCount(); ++i)
    {
        day->getMaterial(i).setTexture(1, night->getMaterial(i).getTexture(0));
        night->getMaterial(i).setTexture(1, day->getMaterial(i).getTexture(0));
    }

    // Create Day/Night pair for Weather w
    _skyboxes[w] = std::make_pair(day, night);
}

scene::ISceneNode * SkyboxModule::createSkybox(const std::string & path)
{
    scene::ISceneNode * skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture((RESOURCES_PATH + path + "_up.jpg").c_str()),
        driver->getTexture((RESOURCES_PATH + path + "_dn.jpg").c_str()),
        driver->getTexture((RESOURCES_PATH + path + "_lf.jpg").c_str()),
        driver->getTexture((RESOURCES_PATH + path + "_rt.jpg").c_str()),
        driver->getTexture((RESOURCES_PATH + path + "_ft.jpg").c_str()),
        driver->getTexture((RESOURCES_PATH + path + "_bk.jpg").c_str()));
    skybox->setVisible(false);

    skybox->setMaterialType((video::E_MATERIAL_TYPE)_shader);

    return skybox;
}

int SkyboxModule::update()
{
	return 0;
}

void SkyboxModule::setSkybox(bool night, int weather)
{
    _active->setVisible(false);

    _night = night;
    _weather = static_cast<AWeather::E_WEATHER>(weather);
    if (!_night)
        _active = _skyboxes[_weather].first;
    else
        _active = _skyboxes[_weather].second;

    _active->setMaterialFlag(video::EMF_FOG_ENABLE, false);
    _active->setVisible(true);
}

void SkyboxModule::OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
{
    // Get variables for ModelViewProjection matrix
    core::matrix4 projection = driver->getTransform(video::ETS_PROJECTION);
    core::matrix4 view = driver->getTransform(video::ETS_VIEW);
    core::matrix4 model = driver->getTransform(video::ETS_WORLD);

    // Create MVP
    core::matrix4 ModViewProj = projection;
    ModViewProj *= view;
    ModViewProj *= model;

    // Send MVP to shader
    services->setVertexShaderConstant("ModViewProj", ModViewProj.pointer(), 16);

    // Send Textures to shader
    int var0 = 0;
    int var1 = 1;
    services->setPixelShaderConstant("texture_skybox1", &var0, 1);
    services->setPixelShaderConstant("texture_skybox2", &var1, 1);

    // Send mixFactor to shader
    services->setPixelShaderConstant("mixFactor", &_mixFactor, 1);
}


int SkyboxModule::update()
{
    // Get elapsedTime
    irr::u32 time = _timer->getTime();
    float elapsedTime = _timer->getElapsedTime();
    time %= static_cast<int>(TIME_OF_DAY);

    // Calc rotation speed for one Day/Night cycle
    float angle = 360.0f / (DAY_LENGTH * 60);
    float speed = angle * elapsedTime;

    // Update skybox rotation
    irr::core::vector3df rot = _active->getRotation();
    rot.Y -= speed;
    _active->setRotation(rot);

    // Calc mixFactor's Skyboxes depending on time
    _mixFactor = 0;
    // Dawn start
    if (time >= DAWN_START)
        _mixFactor = (TIME_OF_DAY - time) /
                     (TIME_OF_DAY - DAWN_START);

    // Twilight end / Night start
    else if (time >= NIGHT_START)
        _mixFactor = 1;

    // Twilight start
    else if (time >= TWILIGHT_START)
        _mixFactor = (time - TWILIGHT_START) /
                     (NIGHT_START - TWILIGHT_START);
 
    return 0;
}
