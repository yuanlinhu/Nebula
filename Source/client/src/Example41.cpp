#include "Example41.h"
#include <vector>
#include <string>

Example41::Example41( void )
{

}

void Example41::createScene( void )
{
	Ogre::Light* light = mSceneMgr->createLight("light1");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(1,-1,0));

	Ogre::Light* mainLight = mSceneMgr->createLight("MainLight");
	mainLight->setPosition(20, 80, 50);

	std::vector<std::string> str_vec;
	str_vec.push_back(mSceneMgr->getTypeName());
	str_vec.push_back(mSceneMgr->getName());
	;

	int ii = 0;
	ii++;
}

void Example41::chooseSceneManager( void )
{
	std::string pkStr = "../../media/packs/chiropteraDM.pk3";
	
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(pkStr, "Zip",
		Ogre::ResourceGroupManager::getSingleton().getWorldResourceGroupName(), true);

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(
		Ogre::ResourceGroupManager::getSingleton().getWorldResourceGroupName());

	mSceneMgr = mRoot->createSceneManager("BspSceneManager");

	mSceneMgr->setWorldGeometry("maps/chiropteradm.bsp");
}

