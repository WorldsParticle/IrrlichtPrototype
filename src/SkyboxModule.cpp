#include "SkyboxModule.h"
#include "Configuration.h"

int SkyboxModule::init()
{
	// add a nice skybox

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	_skybox = smgr->addSkyBoxSceneNode(
		driver->getTexture(RESOURCES_PATH "/irrlicht2_up.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_dn.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_lf.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_rt.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_ft.jpg"),
		driver->getTexture(RESOURCES_PATH "/irrlicht2_bk.jpg"));

	_skydome = smgr->addSkyDomeSceneNode(driver->getTexture(RESOURCES_PATH "/skydome.jpg"), 16, 8, 0.95f, 2.0f);

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	activeNight(false);

	return 0;
}

int SkyboxModule::update()
{
	//nothing to do
	return 0;
}

void SkyboxModule::activeNight(bool n)
{
	_night = n;
	_skybox->setVisible(!_night);
	_skydome->setVisible(_night);
}
