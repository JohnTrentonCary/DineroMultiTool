all: configInfo.h CacheLevel.h CacheConfiguration.h ThreadSafeQueue.h QueueItem.h ConfigBuilder.h Utility.h ConfigRunner.h ConfigAnalyzer.h
	g++ Dinero.cpp CacheLevel.cpp CacheConfiguration.cpp ConfigBuilder.cpp Utility.cpp ConfigRunner.cpp ConfigAnalyzer.cpp -lncurses -std=c++11 -fopenmp -o DineroMultiTool
