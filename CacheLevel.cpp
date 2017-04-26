#include "CacheLevel.h"

CacheLevel::CacheLevel(int s, int bs, int sbs, int a, int mp, int f, int h, int mr)
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

void CacheLevel::setValue(std::string type, int configValue)
{
	if (type == "Size")
		size = configValue;
	else if (type == "BlockSize")
		blockSize = configValue;
	else if (type == "SubBlock Size")
		subBlockSize = configValue;
	else if (type == "Associtivity")
		associtivity = configValue;
	else if (type == "Hit")
		hit = configValue;
	else if (type == "Miss Rate")
		missRate = configValue;
}

bool CacheLevel::canContinue(std::string type, int value)
{
	if (type == "BlockSize" &&
		size >= value)
		return true;
	else if (type == "SubBlock Size" &&
		(blockSize == value || value == 0))
		return true;
	
	return false;

}