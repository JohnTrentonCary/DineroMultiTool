#include <climits>
#include "CacheLevel.h"
#include "Utility.h"

CacheLevel::CacheLevel(int s, int bs, int sbs, int a, int mp, int f, int h, double mr)
{
	size = s;
	blockSize = bs;
	subBlockSize = sbs;
	associtivity = a;
	hit = h;
	missPenalty = mp;
	fetches = f;
	missRate = mr;
}


CacheLevel::~CacheLevel()
{
}

void CacheLevel::setValue(std::string type, double configValue)
{
	if (type == "Size")
		size = (int)configValue;
	else if (type == "BlockSize")
		blockSize = (int)configValue;
	else if (type == "SubBlock Size")
		subBlockSize = (int)configValue;
	else if (type == "Associativity")
		associtivity = (int)configValue;
	else if (type == "Hit")
		hit = (int)configValue;
	else if (type == "Miss")
		missPenalty = (int)configValue;
	else if (type == "Miss Rate")
		missRate = configValue;
	else if (type == "Fetches")
		fetches = (int)configValue;
}

bool CacheLevel::canContinue(std::string type, double value)
{
	int newValue = value;
	if (type == "Associativity" &&
			size >= blockSize * newValue)
		return true;

	if (type == "BlockSize" &&
		size >= newValue)
		return true;

	if (type == "SubBlock Size" &&
		blockSize >= newValue &&
		newValue != 0 &&
		Utility::isPowerOf2(newValue))
		return true;

	return false;
}

double CacheLevel::getValue(std::string type)
{
	if (type == "Size")
		return size;
	else if (type == "BlockSize")
		return blockSize;
	else if (type == "SubBlock Size")
		return subBlockSize;
	else if (type == "Associativity")
		return associtivity;
	else if (type == "Hit")
		return hit;
	else if (type == "Miss")
		return missPenalty;
	else if (type == "Miss Rate")
		return missRate;
	else if (type == "Fetches")
		return fetches;
}

double CacheLevel::calcCPI(double missP)
{
	if (missRate == -1 || missPenalty == -1 || hit == -1)
		return -1;

	if(missP == -1)
		return hit + missRate * missPenalty;
	else
		return hit + missRate * missP;
}
