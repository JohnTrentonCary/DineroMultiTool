#include <cstdlib>
#include <map>
#include <iostream>
#include <string>
#include <climits>

#include "CacheConfiguration.h"
#include "configInfo.h"


CacheConfiguration::CacheConfiguration()
	: L1Instruction(),
	L1Data(),
	L2(),
	L3()
{
}

CacheConfiguration::~CacheConfiguration()
{
}

void CacheConfiguration::setCacheValue(const std::string config, const std::string value)
{
	std::string level = configInfo[config]["level"];
	std::string type = configInfo[config]["type"];

	double configValue = atof(value.c_str());

	if (level == "Instruction")
		L1Instruction.setValue(type, configValue);
	else if (level == "Data")
		L1Data.setValue(type, configValue);
	else if (level == "Level 2")
		L2.setValue(type, configValue);
	else if (level == "Level 3")
		L3.setValue(type, configValue);
}

bool CacheConfiguration::canContinue(const std::string config, std::string value)
{
	std::string type = configInfo[config]["type"];

	if (type == "Size" ||
		type == "Hit" ||
		type == "Miss")
		return true;

	std::string level = configInfo[config]["level"];
	int configValue = atoi(value.c_str());

	//Block size must be <= the size of that cache
	if (level == "Instruction")
		return L1Instruction.canContinue(type, configValue);
	else if (level == "Data")
		return L1Data.canContinue(type, configValue);
	else if (level == "Level 2")
		return L2.canContinue(type, configValue);
	else if (level == "Level 3")
		return L3.canContinue(type, configValue);

	std::cout << "Error: Unrecognized configuration parameter: " << config << '\n';
	exit(EXIT_FAILURE);
}

bool CacheConfiguration::canAddToCommand(const std::string name)
{
	if (configInfo[name]["type"] == "Hit" ||
		configInfo[name]["type"] == "Miss")
		return false;

	return true;
}

double CacheConfiguration::getValue(const std::string level,const std::string type)
{
	if (level == "Instruction")
		return L1Instruction.getValue(type);
	else if (level == "Data")
		return L1Data.getValue(type);
	else if (level == "Level 2")
		return L2.getValue(type);
	else if (level == "Level 3")
		return L3.getValue(type);
}

void CacheConfiguration::calcCPI()
{
	CPI = -1;
	CPI = L3.calcCPI(CPI);
	CPI = L2.calcCPI(CPI);

	double instCPI = L1Instruction.calcCPI(CPI);
	double dataCPI = L1Data.calcCPI(CPI);

	if(instCPI != -1)
	{
		if(dataCPI != -1)
			CPI = instCPI + ((double)L1Data.fetches / (double)L1Instruction.fetches) * dataCPI;
		else
			CPI = instCPI * 2;
	}
	else if (dataCPI != -1)
		CPI = dataCPI * 2;
}
