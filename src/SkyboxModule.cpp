#include "SkyboxModule.h"
#include "Configuration.h"

int SkyboxModule::init()
{
    // Create all pair Day/Night Skyboxes for all weathers
    scene::ISceneNode * day = createSkybox(RESOURCES_PATH "/Day/day");
	scene::ISceneNode * night = createSkybox(RESOURCES_PATH "/Night/night");
    _skyboxes[AWeather::E_WEATHER::NONE] = std::make_pair(day, night);

    day = createSkybox(RESOURCES_PATH "/Rain_Day/rainDay");
    night = createSkybox(RESOURCES_PATH "/Rain_Night/rainNight");
    _skyboxes[AWeather::E_WEATHER::RAIN] = std::make_pair(day, night);

    day = createSkybox(RESOURCES_PATH "/Snow_Day/snowDay");
    night = createSkybox(RESOURCES_PATH "/Snow_Night/snowNight");
    _skyboxes[AWeather::E_WEATHER::SNOW] = std::make_pair(day, night);

    _active = _skyboxes[_weather].first;
    _active->setVisible(true);

	return 0;
}

scene::ISceneNode * SkyboxModule::createSkybox(const std::string & path)
{
    scene::ISceneNode * skybox = smgr->addSkyBoxSceneNode(
        driver->getTexture((path + "_up.jpg").c_str()),
        driver->getTexture((path + "_dn.jpg").c_str()),
        driver->getTexture((path + "_lf.jpg").c_str()),
        driver->getTexture((path + "_rt.jpg").c_str()),
        driver->getTexture((path + "_ft.jpg").c_str()),
        driver->getTexture((path + "_bk.jpg").c_str()));
    skybox->setVisible(false);

    return skybox;
}

int SkyboxModule::update()
{
	//nothing to do
	return 0;
}

void SkyboxModule::activate(bool night)
{
    // Will ultimately be activate(night, weather)
    _active->setVisible(false);

    _night = night;
    if (!_night)
        _active = _skyboxes[_weather].first;
    else
        _active = _skyboxes[_weather].second;

    _active->setVisible(true);
}