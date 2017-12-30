
#ifndef __ENTITY_CSV_H__
#define __ENTITY_CSV_H__


#include "BaseApplication.h"

#include "csvReader.h"



class EntityCsv
{
public:
	enum
	{
		ID				= 0 ,
		NAME			= 1 ,
		MESH_NAME		= 2 ,
		SCALE_X			= 3 ,
		SCALE_Y			= 4 ,
		SCALE_Z			= 5 ,
		POS_X			= 6 ,
		POS_Y			= 7 ,
		POS_Z			= 8 ,
	};

	EntityCsv();

public:
	int id;
	std::string name;
	std::string mesh_name;
	int scale_x;
	int scale_y;
	int scale_z;
	int pos_x;
	int pos_y;
	int pos_z;
};


#endif	//__ENTITY_CSV_H__

