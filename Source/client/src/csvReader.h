#pragma once

#include <vector>
#include <string>
#include <map>

//csv表的一行数据
class CsvData
{
public:
	CsvData();
	~CsvData();

	void parseRow(const std::string& rowData);

	int getIntVal(int index);
	std::string getStringVal(int index);

public:

	static void SplitString(const std::string& str, const std::string& seperator, std::vector<std::string>& retList);


private:
	std::string& getValue(int index);

private:

	std::vector<std::string> mDataList;		//数据
};


//单个csv文件的分析
class CsvFile
{
public:
	CsvFile();
	~CsvFile();

	void loadFile(const std::string& fileName);

	std::vector<CsvData*>& getCsvDataList();


private:
	std::vector<CsvData*> mCsvDataList;
};