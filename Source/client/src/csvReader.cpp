#include "csvReader.h"
#include <fstream>

CsvData::CsvData()
{

}

CsvData::~CsvData()
{

}

std::string& CsvData::getValue(int index)
{
	return mDataList[index];
}

int CsvData::getIntVal(int index)
{
	return atoi(getValue(index).c_str());
}

std::string CsvData::getStringVal(int index)
{
	return getValue(index);
}

void CsvData::parseRow(const std::string& rowData)
{
	CsvData::SplitString(rowData, ",", mDataList);
}

void CsvData::SplitString(const std::string& str, const std::string& seperator, std::vector<std::string>& retList)
{
	retList.clear();

	size_t nStartPosFound = str.find(seperator, 0);
	size_t nFieldStart = 0;

	for (; nStartPosFound != -1; nStartPosFound = str.find(seperator, nStartPosFound))
	{
		std::string strSub = str.substr(nFieldStart, nStartPosFound - nFieldStart);
		nStartPosFound += seperator.size();
		nFieldStart = nStartPosFound;

		retList.push_back(strSub);
	}

	//加入最后一个字段
	if (nFieldStart < str.size())
	{
		std::string strSub = str.substr(nFieldStart, str.size() - nFieldStart);
		retList.push_back(strSub);
	}

}



////////////////////////////////////////////////////////////////////////////
CsvFile::CsvFile()
{

}

CsvFile::~CsvFile()
{

}

void CsvFile::loadFile(const std::string& fileName)
{
	std::ifstream fileStream(fileName.c_str());
	//fileStream.open(fileName.c_str());
	
	int id = 0;
	char buffer[4096] = { 0 };
	while (!fileStream.eof())
	{
		id++;
		fileStream.getline(buffer, 4096);
		if (std::string(buffer).empty())
		{
			break;
		}

		if (id == 1 || id == 2)
		{
			//第一行是描述， 忽略掉
			continue;
		}

		CsvData* newCsvData = new CsvData();
		newCsvData->parseRow(buffer);

		mCsvDataList.push_back(newCsvData);
	}
}


std::vector<CsvData*>& CsvFile::getCsvDataList()
{
	return mCsvDataList;
}