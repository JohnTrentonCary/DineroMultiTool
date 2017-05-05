#pragma once

#include "CacheLevel.h"
#include <vector>

class CacheConfiguration
{
	CacheLevel L1Instruction;
	CacheLevel L1Data;
	CacheLevel L2;
	CacheLevel L3;

public:
	double CPI;

	CacheConfiguration();
	~CacheConfiguration();

	void setCacheValue(const std::string config, const std::string value);
	bool canContinue(const std::string config, std::string value);
	static bool canAddToCommand(const std::string type);
	double getValue(const std::string level, const std::string type);
	void calcCPI();
};
