#include "ElementsModule.h"

int ElementsModule::init(){

	IAnimatedMesh* mesh = smgr->getMesh("./ressources/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("./ressources/sydney.bmp"));
	}
	node->setPosition(core::vector3df(2397 * 2, 343 * 2, 2700 * 2));
	node->setScale(node->getScale() * 10);
	return 0;
}
int ElementsModule::update(){
	//nothing to do
	return 0;
}

