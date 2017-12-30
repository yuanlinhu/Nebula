#include "EntityCsvManager.h"
#include "EntityCsv.h"
#include "csvReader.h"


EntityCsvManager::EntityCsvManager()
{

}

EntityCsvManager::~EntityCsvManager()
{

}

void EntityCsvManager::loadFile()
{
	CsvFile csvFile;
	csvFile.loadFile("entity.csv");

	std::vector<CsvData*>& csvList = csvFile.getCsvDataList();
	for (std::vector<CsvData*>::iterator iter = csvList.begin(); iter != csvList.end(); ++iter)
	{
		CsvData* csvData = *iter;
		EntityCsv* newEntityCsv = new EntityCsv();
		newEntityCsv->id		= csvData->getIntVal(EntityCsv::ID);
		newEntityCsv->name		= csvData->getStringVal(EntityCsv::NAME);
		newEntityCsv->mesh_name = csvData->getStringVal(EntityCsv::MESH_NAME);
		newEntityCsv->scale_x	= csvData->getIntVal(EntityCsv::SCALE_X);
		newEntityCsv->scale_y	= csvData->getIntVal(EntityCsv::SCALE_Y);
		newEntityCsv->scale_z	= csvData->getIntVal(EntityCsv::SCALE_X);
		newEntityCsv->pos_x		= csvData->getIntVal(EntityCsv::POS_X);
		newEntityCsv->pos_y		= csvData->getIntVal(EntityCsv::POS_Y);
		newEntityCsv->pos_z		= csvData->getIntVal(EntityCsv::POS_X);

		mEntityCsvList.push_back(newEntityCsv);
	}
}

std::vector<EntityCsv*>& EntityCsvManager::getEntityCsvList()
{
	return mEntityCsvList;
}

EntityCsv* EntityCsvManager::getEntityCsvById( int id )
{
	EntityCsv* retEntityCsv = NULL;
	for (std::vector<EntityCsv*>::iterator iter = mEntityCsvList.begin(); iter != mEntityCsvList.end(); ++iter)
	{
		EntityCsv* entityCsv = *iter;

		if(entityCsv->id == id)
		{
			retEntityCsv = entityCsv;
			break;
		}
	}

	return retEntityCsv;
}

