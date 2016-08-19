#include "SkyboxModule.h"

int SkyboxModule::init(){

	// add a nice skybox

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	smgr->addSkyBoxSceneNode(
		driver->getTexture("./ressources/irrlicht2_up.jpg"),
		driver->getTexture("./ressources/irrlicht2_dn.jpg"),
		driver->getTexture("./ressources/irrlicht2_lf.jpg"),
		driver->getTexture("./ressources/irrlicht2_rt.jpg"),
		driver->getTexture("./ressources/irrlicht2_ft.jpg"),
		driver->getTexture("./ressources/irrlicht2_bk.jpg"));

	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);

	return 0;
}
int SkyboxModule::update(){
	//nothing to do
	return 0;
}

