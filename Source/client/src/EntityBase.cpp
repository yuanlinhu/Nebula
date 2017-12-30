#include "EntityBase.h"

EntityBase::EntityBase( EntityCsv* entityCsv, Ogre::Entity* entity, Ogre::SceneNode* scene, int index)
{
	mIndex			= index;
	mEntityCsv		= entityCsv;
	mEntity			= entity;
	mSceneNode		= scene;
}

EntityBase::~EntityBase()
{
	mIndex			= 0;
	mEntityCsv		= NULL;
	mEntity			= NULL;
	mSceneNode		= NULL;
}

Ogre::Entity* EntityBase::getEntity()
{
	return mEntity;
}

Ogre::SceneNode* EntityBase::getSceneNode()
{
	return mSceneNode;
}
