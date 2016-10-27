#include "module/SkyboxModule.h"
#include "Configuration.h"

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

    // Init timer
    _timer = device->getTimer();

	return 0;
}


void SkyboxModule::createSkyboxesPair(AWeather::E_WEATHER w, const std::string & pathDay, const std::string & pathNight)
{
    // Create Day and Night Skybox
    scene::ISceneNode * day = createSkybox(pathDay);
    scene::ISceneNode * night = createSkybox(pathNight);

    // Create new Texture layer with the opposite time Skybox.
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


void SkyboxModule::setSkybox(bool night, int weather)
{
    _active->setVisible(false);

    _night = night;
    _weather = static_cast<AWeather::E_WEATHER>(weather);
    if (!_night)
        _active = _skyboxes[_weather].first;
    else
        _active = _skyboxes[_weather].second;

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
    float elapsedTime = (time - _lastTime) / 1000.0f;
    _lastTime = time;
    time %= (int)(TIME_OF_DAY * 60 * 1000);

    // Calc rotation speed for a TIME_OF_DAY(min) Day/Night cycle
    float angle = 360.0f / (TIME_OF_DAY * 60);
    float speed = angle * elapsedTime;

    // Update skybox rotation
    irr::core::vector3df rot = _active->getRotation();
    rot.Y -= speed;
    _active->setRotation(rot);

    // Stuff to mix Skyboxes depending on time
    _mixFactor = 0;
    // Dawn start
    if (time >= DAWN_START * 60 * 1000)
        _mixFactor = (TIME_OF_DAY * 60 * 1000 - time) /
                     (TIME_OF_DAY * 60 * 1000 - DAWN_START * 60 * 1000);
    // Twilight end / Night start
    else if (time >= NIGHT_START * 60 * 1000)
        _mixFactor = 1;
    // Twilight start
    else if (time >= TWILIGHT_START * 60 * 1000)
        _mixFactor = (time - TWILIGHT_START * 60 * 1000) /
                     (NIGHT_START * 60 * 1000 - TWILIGHT_START * 60 * 1000);
 
    return 0;
}
