
#ifndef __ENTITY_CSV_MANAGER_H__
#define __ENTITY_CSV_MANAGER_H__


#include "BaseApplication.h"


class EntityCsv;

class EntityCsvManager
{
public:
	EntityCsvManager();
	~EntityCsvManager();

	void loadFile();

	std::vector<EntityCsv*>&		getEntityCsvList();
	EntityCsv*						getEntityCsvById(int id);

private:
	std::vector<EntityCsv*>		mEntityCsvList;
};


#endif	//__ENTITY_CSV_MANAGER_H__

