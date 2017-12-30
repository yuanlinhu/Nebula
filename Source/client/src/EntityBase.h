
#ifndef __ENTITY_BASE_H__
#define __ENTITY_BASE_H__


#include "BaseApplication.h"

#include "csvReader.h"


class EntityCsv;

class EntityBase
{
public:
	EntityBase(EntityCsv* entityCsv, Ogre::Entity* entity, Ogre::SceneNode* scene, int index);
	~EntityBase();


	Ogre::Entity*			getEntity();
	Ogre::SceneNode*		getSceneNode();

private:
	int						mIndex;
	EntityCsv*				mEntityCsv;

	Ogre::Entity*			mEntity;
	Ogre::SceneNode*		mSceneNode;


private:
	EntityBase();
};


#endif	//__ENTITY_BASE_H__

