#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <map>

#include "CacheConfiguration.h"
#include "configInfo.h"
#include "ThreadSafeQueue.h"
#include "QueueItem.h"
#include "ConfigBuilder.h"
#include "ConfigRunner.h"
#include "ConfigAnalyzer.h"

volatile bool isFinished = false;

extern std::map<std::string, std::map<std::string, std::string> > configInfo;

int main(int argc, char const *argv[])
{
	if (argc == 1) {
		std::cout << "Please include a Dinero MultiConfigurations file" << std::endl;
		return 0;
	}

	std::cout << "Opening File.";

	std::ifstream inFile;
	inFile.open(argv[1]);

	std::cout << "..........Complete\n";

	//Get all of the data into the 2D vector
	ConfigBuilder builder;
	builder.processFile(inFile);
	inFile.close();

	builder.constructConfigs();

	ConfigRunner runner;
	runner.runConfigs(builder);

	ConfigAnalyzer::populateStoredConfigs(builder);
	ConfigAnalyzer::buildBenchFiles(builder);
	// cout << "Collecting File information.";

	return 0;
}
