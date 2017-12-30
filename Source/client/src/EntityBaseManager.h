
#ifndef __ENTITY_BASE_MANAGER_H__
#define __ENTITY_BASE_MANAGER_H__


#include "BaseApplication.h"

#include "csvReader.h"


class EntityBase;
class EntityCsvManager;

namespace Ogre
{
	class SceneManager;
}

class EntityBaseManager
{
public:
	EntityBaseManager(Ogre::SceneManager* sceneMgr);
	~EntityBaseManager();


	void		loadEntity();
	EntityBase* createEntity(int id, int x, int y, int z);
	EntityBase* createEntity(int id);
	void		addEntity(int id, EntityBase* entity);

private:
	int maxIndex;
	std::map<int, EntityBase*>	mEntityManager;
	EntityCsvManager*			mEntityCsvManager;
	Ogre::SceneManager*			mSceneManager;
};


#endif	//__ENTITY_BASE_MANAGER_H__

