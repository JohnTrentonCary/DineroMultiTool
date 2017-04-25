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
	CacheConfiguration();
	~CacheConfiguration();

	void setCacheValue(std::string config, std::string value);
	bool canContinue(std::string config, std::string value);
	static bool canAddToCommand(std::string type);
};

