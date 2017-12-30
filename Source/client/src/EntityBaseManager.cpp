
#include "EntityBaseManager.h"
#include "EntityBase.h"
#include "EntityCsvManager.h"
#include "EntityCsv.h"

EntityBaseManager::EntityBaseManager(Ogre::SceneManager* sceneMgr)
{
	mSceneManager = sceneMgr;
	mEntityCsvManager = new EntityCsvManager();

	maxIndex = 0;
}

EntityBaseManager::~EntityBaseManager()
{

}


void EntityBaseManager::loadEntity()
{
	mEntityCsvManager->loadFile();
}

EntityBase* EntityBaseManager::createEntity(int id, int x, int y, int z)
{

	EntityBase* newEntity = createEntity(id);
	if(NULL != newEntity)
	{
		newEntity->getSceneNode()->setPosition(Ogre::Vector3(x, y, z));
	}

	return newEntity;
}

EntityBase* EntityBaseManager::createEntity(int id)
{
	EntityCsv* entityCsv = mEntityCsvManager->getEntityCsvById(id);

	maxIndex++;
	std::stringstream ss;
	//ss<<entityCsv->id;
	ss<<maxIndex;
	std::string entityName;
	ss>>entityName;
	entityName += "_entity";

	Ogre::Entity* newEntity = mSceneManager->createEntity(entityName, entityCsv->mesh_name);
	Ogre::SceneNode* newNode = mSceneManager->getRootSceneNode()->createChildSceneNode(entityName);

	newNode->setScale(Ogre::Vector3(entityCsv->scale_x, entityCsv->scale_y, entityCsv->scale_z));
	newNode->setPosition(Ogre::Vector3(entityCsv->pos_x, entityCsv->pos_y, entityCsv->pos_z));
	newNode->attachObject(newEntity);

	EntityBase* newEntityBase = new EntityBase(entityCsv, newEntity, newNode, maxIndex);

	this->addEntity(id, newEntityBase);

	return newEntityBase;
}

void EntityBaseManager::addEntity( int id, EntityBase* entity )
{
	mEntityManager[id] = entity;
}
