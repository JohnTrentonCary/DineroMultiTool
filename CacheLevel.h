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
	double missRate;

	CacheLevel(int s = -1, int bs = -1, int sbs = -1, int a = -1, int h = -1, int mp = -1, int f = -1, double mr = -1);
	~CacheLevel();
	void setValue(std::string type, double configValue);
	bool canContinue(std::string type, double value);
	double getValue(std::string type);
	double calcCPI(double missP);
};
