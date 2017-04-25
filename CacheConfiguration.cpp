#include <cstdlib>
#include <map>

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

void CacheConfiguration::setCacheValue(std::string config, std::string value)
{
	std::string level = configInfo[config]["level"];
	std::string type = configInfo[config]["type"];

	int configValue = atoi(value.c_str());

	if (level == "Instruction")
		L1Instruction.setValue(type, configValue);
	else if (level == "Data")
		L1Data.setValue(type, configValue);
	else if (level == "Level 2")
		L2.setValue(type, configValue);
	else if (level == "Level 3")
		L3.setValue(type, configValue);
}

bool CacheConfiguration::canContinue(std::string config, std::string value)
{
	std::string type = configInfo[config]["type"];

	if (type == "Size" ||
		type == "Associtivity" || 
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

	return false;
}

bool CacheConfiguration::canAddToCommand(std::string name)
{
	if (configInfo[name]["type"] == "Hit" ||
		configInfo[name]["type"] == "Miss")
		return false;

	return true;
}