#pragma once

#include <string>

class CacheLevel
{
public:
	int size;
	int blockSize;
	int subBlockSize;
	int associtivity;
	int hit;
	int missPenalty;
	int fetches;
	int missRate;

	CacheLevel(int s = -1, int bs = -1, int sbs = -1, int a = -1, int h = -1, int mp = -1, int f = -1, int mr = -1);
	~CacheLevel();
	void setValue(std::string type, int configValue);
	bool canContinue(std::string type, int value);
};

