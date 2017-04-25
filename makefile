all: configInfo.h CacheLevel.h CacheConfiguration.h ThreadSafeQueue.h QueueItem.h
	g++ Dinero.cpp CacheLevel.cpp CacheConfiguration.cpp -lncurses -std=c++11 -fopenmp -o DineroMultiTool
