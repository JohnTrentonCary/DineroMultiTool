#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstring>
#include <cmath>
#include <map>

#include <mutex>
#include <thread>
#include <string>
#include <unistd.h>                  /*  for sleep()  */
#include <ncurses.h>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>

#include "CacheConfiguration.h"
#include "configInfo.h"
#include "ThreadSafeQueue.h"
#include "QueueItem.h"

volatile bool isFinished = false;

extern std::map<std::string, std::map<std::string, std::string> > configInfo;

bool isRange(std::string value)
{
	if (strstr(value.c_str(), ":") == NULL) {
		return false;
	}

	return true;
}

std::vector<std::string> split(std::string words, char delimiter)
{
	std::string segment;
	std::stringstream range(words);
	std::vector<std::string> seglist;
	while (getline(range, segment, delimiter))
	{
		seglist.push_back(segment);
	}

	return seglist;
}

void buildExec(std::vector< std::vector<std::string> > &configs, std::string &commands, std::string delimiter)
{
	for (int i = 0; i < configs.size(); i++)
	{
		if (configs[i][0] == delimiter)
		{
			commands = configs[i][1];
			configs.erase(configs.begin() + i);
			break;
		}
	}
}

int findSpecificPos(std::vector< std::vector<std::string> > &configs, std::string delimiter)
{
	for (int i = 0; i < configs.size(); i++)
	{
		if (configs[i][0] == delimiter)
		{
			return i;
		}
	}

	return -1;
}

void buildConfigs(std::vector< std::vector< std::string> > configs,
	std::vector<std::string> &builtCommands,
	std::vector<CacheConfiguration> &storedConfigs,
	CacheConfiguration currentConfig,
	std::string executeCommand,
	std::string benchmarkCommand,
	int configPos = 0)
{
	int iterations = configs[configPos].size();

	//Base case
	if (configPos == configs.size() - 1)
	{
		for (int i = 1; i < iterations; i++)
		{
			std::string configName = configs[configPos][0];
			std::string configValue = configs[configPos][i];

			//check if it is safe to use the current value
			bool canContinue = currentConfig.canContinue(configName, configValue);
			if (!canContinue)
				continue;

			currentConfig.setCacheValue(configName, configValue);

			std::string finalCommand = executeCommand;
			if (CacheConfiguration::canAddToCommand(configName))
			{
				//If it is, add it to the command
				finalCommand += " " + configInfo[configName]["flag"];
				finalCommand += " " + configValue + " " + benchmarkCommand;
				finalCommand += configInfo[configName]["naming"] + configValue + ".txt";
			}

			//std::cout << finalCommand << std::endl;
			builtCommands.push_back(finalCommand);
			storedConfigs.push_back(currentConfig);
		}
	}
	else
	{
		for (int i = 1; i < iterations; i++)
		{
			std::string configName = configs[configPos][0];
			std::string configValue = configs[configPos][i];

			//check if it is safe to use the current value
			bool canContinue = currentConfig.canContinue(configName, configValue);
			if (!canContinue)
				continue;

			currentConfig.setCacheValue(configName, configValue);

			std::string newBenchmarkCommand = benchmarkCommand;
			std::string newExecuteCommand = executeCommand;
			//Check it is something that is suppose to be added to the command or just the configuration instance
			if (CacheConfiguration::canAddToCommand(configName))
			{
				newBenchmarkCommand = benchmarkCommand + configInfo[configName]["naming"] + configValue;
				newExecuteCommand = executeCommand + " " + configInfo[configName]["flag"];
				newExecuteCommand += " " + configValue;
			}

			buildConfigs(configs, builtCommands, storedConfigs, currentConfig, newExecuteCommand, newBenchmarkCommand, configPos + 1);
		}
	}
}

std::vector< std::vector<std::string> > processFile(std::ifstream &inFile)
{
	std::string line;
	std::vector< std::vector<std::string> > configs;
	while (!inFile.eof()) {
		getline(inFile, line);

		//Make sure the line isn't blank
		if (line.length() < 7)
			continue;

		//Split the line up into its parts
		std::vector< std::string> newConfigSet = split(line, ' ');

		//Check if any nodes have a range
		for (int i = 1; i < newConfigSet.size(); i++) {

			if (isRange(newConfigSet[i])) {
				std::vector<std::string> ranges = split(newConfigSet[i], ':');

				int min = atoi(ranges[0].c_str()), max = atoi(ranges[1].c_str());

				std::vector< std::string> newRange;

				for (int i = min; i < max + 1; i++)
				{
					newRange.push_back(std::to_string(i));
				}

				std::vector<std::string>::iterator currentPos = newConfigSet.begin() + i + 1;
				newConfigSet.insert(currentPos, newRange.begin(), newRange.end());
				newConfigSet.erase(newConfigSet.begin() + i);
				i += ranges.size() - 1;
			}
		}

		//Check if the values were listed as powers
		int firstWordLength = newConfigSet[0].length();
		if (newConfigSet[0][firstWordLength - 2] == 'P')
		{
			//If they were listed as power, convert them to the actual values
			for (int i = 1; i < newConfigSet.size(); i++)
			{
				int realValue = atoi(newConfigSet[i].c_str());
				if (realValue != 0)
					realValue = pow(2, realValue);

				newConfigSet[i] = std::to_string(realValue);
			}
			newConfigSet[0].erase(newConfigSet[0].end() - 2);
		}

		configs.push_back(newConfigSet);
	}

	return configs;
}

void BackgroundJob(std::vector<std::string> configsToRun, ThreadSafeQueue<QueueItem> &safeQueue)
{
	#pragma omp parallel for
	for (int i = 0; i < configsToRun.size(); i++) {
		QueueItem newItem;
		newItem.id = i;
		newItem.status = 2;
		safeQueue.Enqueue(newItem);

		//Swap these for PRODUCTION
		usleep(50000);
		// system(configsToRun[i]);

		newItem.status = 3;
		safeQueue.Enqueue(newItem);
	}

	isFinished = true;
}

void runConfigs(std::vector<std::string> benchmarks,
 							std::vector<std::string> builtConfigs)
{
	WINDOW *mainwin;
	if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}

	int benchSize = benchmarks.size() - 1;
	int totalConfigs = builtConfigs.size();
	int configsPerBenchmark = totalConfigs / benchSize;
	int width;

	if (configsPerBenchmark < 100)
		width = configsPerBenchmark;
	else
		width = 100;

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);

	color_set(1, NULL);
	// std::string tempBench = "Benchmark: ";

	for (int i = 0; i < benchSize; i++) {
		std::string output = benchmarks[i + 1];
		int lenDif = width - output.length();

		if (lenDif < 0)
		{
			std::string::iterator strIt;
			std::string out1;
			// out1.insert(out1.end(), output, configsPerBenchmark);
			out1.insert( strIt, output.begin(), output.begin() + configsPerBenchmark);
			mvaddstr( i + 1, 0, out1.c_str());

			color_set(4, NULL);
			std::string out2;
			out2.insert(out2.end(), output[configsPerBenchmark], -lenDif);
			mvaddstr(i + 1, configsPerBenchmark, out2.c_str());

			color_set(1, NULL);
		}
		else
		{
			output.insert(output.end(), lenDif, ' ');

			mvaddstr(i + 1, 0, output.c_str());
		}
		refresh();
	}

	ThreadSafeQueue<QueueItem> safeQueue;

	std::thread BackgroundThread(BackgroundJob, builtConfigs, std::ref(safeQueue));

	std::vector<int> progress(benchSize, 0);
	std::vector<int> complete(benchSize, 0);
	int count = 0;

	while (true)
	{
		QueueItem outValue;

		if (safeQueue.Dequeue(outValue))
		{
			count +=1;
			color_set(4, NULL);
			std::string benchesCompleted = "Simulations Complete: " + std::to_string(count / 2) + "/" + std::to_string(totalConfigs);
			mvaddstr(0,0, benchesCompleted.c_str());

			int benchIndex = (outValue.id / configsPerBenchmark);
			std::string temp = benchmarks[benchIndex + 1];
			int value;

			if (outValue.status == 2)
			{
				progress[benchIndex] += 1;
				value = (progress[benchIndex] * width) / configsPerBenchmark;
			}
			else if (outValue.status == 3) {
				complete[benchIndex] += 1;
				value = (complete[benchIndex] * width) / configsPerBenchmark;
			}

			value -= 1;
			benchIndex += 1;

			color_set(outValue.status, NULL);

			if (value >= temp.length())
				mvaddstr(benchIndex, value, " ");
			else
				mvaddch(benchIndex, value, temp[value]);

			refresh();
		}
		else
		{
			if (isFinished)
				break;

			usleep(1000);
		}
	}

	BackgroundThread.join();

	sleep(3);
	/*  Clean up after ourselves  */

	delwin(mainwin);
	endwin();
	refresh();

}

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
	std::vector< std::vector<std::string> > configs = processFile(inFile);
	inFile.close();

	//This needs to be used in every command to execute Dinero
	std::string command = "";
	buildExec(configs, command, "DineroLocation:");

	//Get the index for benchmarks
	int benchmarkIndex = findSpecificPos(configs, "Benchmarks:");

	if (benchmarkIndex == -1)
	{
		std::cout << "ERROR: Please include a list of benchmarks to run with the like \"Benchmarks: test1.txt test2.txt\"" << std::endl;
		return 0;
	}

	std::vector<std::string> builtConfigs;
	std::vector<std::string> benchmarks = configs[benchmarkIndex];
	std::vector<CacheConfiguration> storedConfigs;
	configs.erase(configs.begin() + benchmarkIndex);

	std::cout << "Generating All Configurations.";
	for (int i = 1; i < benchmarks.size(); i++)
	{
		std::cout << ".";
		std::vector<std::string> bench = split( benchmarks[ i], '/');
		bench = split( bench[ bench.size() - 1], '.');
		std::string benchmarkName = bench[0];
		std::string commandToMakeDir = "mkdir -p " + benchmarkName;

		//SWAP COMMENTS FOR PRODUCTION
		//system(commandToMakeDir.c_str());

		std::string commands[2];
		commands[0] = "";
		commands[1] = "";

		commands[0] = command;
		commands[1] = " <" + benchmarkName + " > ~/" + benchmarkName + "/run";
		CacheConfiguration newConfig;

		buildConfigs(configs, builtConfigs, storedConfigs, newConfig, commands[0], commands[1]);
	}

	std::cout << "Complete" << std::endl;


	runConfigs(benchmarks, builtConfigs);

	// cout << "Collecting File information.";

	return 0;
}
