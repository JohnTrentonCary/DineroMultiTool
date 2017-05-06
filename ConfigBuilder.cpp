#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <climits>
#include <cstdlib>

#include "ConfigBuilder.h"
#include "configInfo.h"
#include "Utility.h"

ConfigBuilder::ConfigBuilder()
{
  threadLimit = 0;
}

void ConfigBuilder::buildConfigs( CacheConfiguration &currentConfig,
                std::string &executeCommand,
                std::string &benchmarkCommand,
                int configPos)
{
  int iterations = configs[configPos].size();
  bool couldCreate  = false;
  std::string configName = configs[configPos][0];

	//Base case
	if (configPos == configs.size() - 1)
	{
		for (int i = 1; i < iterations; i++)
		{
			std::string configValue = configs[configPos][i];

			//check if it is safe to use the current value
			bool canContinue = currentConfig.canContinue(configName, configValue);
			if (!canContinue)
				continue;

      couldCreate = true;
			currentConfig.setCacheValue(configName, configValue);

			std::string finalCommand = executeCommand;
			if (CacheConfiguration::canAddToCommand(configName))
			{
				//If it is, add it to the command
				finalCommand += " " + configInfo[configName]["flag"];
        finalCommand += " " + configValue;
			}

      finalCommand += " " + benchmarkCommand;
      finalCommand += configInfo[configName]["naming"] + configValue + ".txt";

			// std::cout << finalCommand << std::endl;
			builtConfigs.push_back(finalCommand);
			storedConfigs.push_back(currentConfig);
		}
	}
	else
	{
		for (int i = 1; i < iterations; i++)
		{
			std::string configValue = configs[configPos][i];

			//check if it is safe to use the current value
			bool canContinue = currentConfig.canContinue(configName, configValue);
			if (!canContinue)
				continue;

      couldCreate = true;
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

			buildConfigs( currentConfig, newExecuteCommand, newBenchmarkCommand, configPos + 1);
		}
	}

  if (!couldCreate)
  {
    std::cout << std::endl << "Error: Invalid argument or values for: " << configName << std::endl;
    exit(EXIT_FAILURE);
  }
}

void ConfigBuilder::buildExec(std::string &commands, const std::string &delimiter)
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

void ConfigBuilder::processFile(std::ifstream &inFile)
{
  std::cout << "Processing File.";
  std::string line;
	while (!inFile.eof()) {
		getline(inFile, line);

    std::cout << ".";

		//Make sure the line isn't blank
		if (line.length() < 7 || line[0] == '#')
			continue;

		//Split the line up into its parts
    std::vector< std::string> newConfigSet;
		Utility::split(line, ' ', newConfigSet);
    int newConfigSetSize = newConfigSet.size();

    for (int i = 0; i < newConfigSetSize; i++)
      if (newConfigSet[i].length() < 1)
        newConfigSet.erase(newConfigSet.begin() + i);

    if (newConfigSet[0] == "ThreadLimit:")
    {
      threadLimit = atoi(newConfigSet[1].c_str());
      continue;
    }

		int firstWordLength = newConfigSet[0].length();

		//Check if any nodes have a range and remove any extra spaces
		for (int i = 1; i < newConfigSetSize; i++)
    {

      std::cout << ".";

			if (Utility::isRange(newConfigSet[i]))
      {
        std::vector<std::string> ranges;
        Utility::split(newConfigSet[i], ':', ranges);

        //Checks to make sure both numbers are numbers
        char *a, *b;
        strtol(ranges[0].c_str(), &a, 10);
        strtol(ranges[1].c_str(), &b, 10);

        if( *a != '\0')
        {
          std::cout << std::endl << "Error: Invalid range minimum: " << ranges[0] << std::endl;
          exit(EXIT_FAILURE);
        }

        if(*b != '\0')
        {
          std::cout << std::endl << "Error: Invalid range maximum: " << ranges[1] << std::endl;
          exit(EXIT_FAILURE);
        }

				int min = atoi(ranges[0].c_str());
        int max = atoi(ranges[1].c_str());

        //Checks if they are meant to be exponents or not
        if (newConfigSet[0][firstWordLength - 2] != 'P')
        {

          if (!Utility::isPowerOf2(min) ) {
            std::cout << std::endl << "Error: invalid value. The rangre's minimum is not a power of 2: " << min << std::endl;
            exit(EXIT_FAILURE);
          }

          if (!Utility::isPowerOf2(max) ) {
            std::cout << std::endl << "Error: invalid value. The range's maximum is not a power of 2: " << max << std::endl;
            exit(EXIT_FAILURE);
          }
          //If they aren't exponents convert them to exponents so that we can
          // more easily make the range
          min = (int)( log(min) / log(2) );
          max = (int)( log(max) / log(2) );
        }

				std::vector< std::string> newRange;

				for (int i = min; i < max + 1; i++)
				{
          int val = i;
          if (newConfigSet[0][firstWordLength - 2] != 'P')
            val = pow(2, i);

					newRange.push_back(std::to_string(val));
				}
        
				std::vector<std::string>::iterator currentPos = newConfigSet.begin() + i + 1;
				newConfigSet.insert(currentPos, newRange.begin(), newRange.end());
				newConfigSet.erase(newConfigSet.begin() + i);
				i += ranges.size() - 1;
			}
		}

		//Check if the values were listed as powers
		if (newConfigSet[0][firstWordLength - 2] == 'P')
		{
			//If they were listed as power, convert them to the actual values
			for (int i = 1; i < newConfigSet.size(); i++)
			{
        std::cout << ".";

				int realValue = atoi(newConfigSet[i].c_str());
				if (realValue != 0)
					realValue = pow(2, realValue);

				newConfigSet[i] = std::to_string(realValue);
			}
			newConfigSet[0].erase(newConfigSet[0].end() - 2);
		}

		configs.push_back(newConfigSet);
	}
  std::cout << "..Complete" << std::endl;
}

void ConfigBuilder::constructConfigs()
{
  	//This needs to be used in every command to execute Dinero
  	std::string command = "";
  	buildExec( command, "DineroLocation:");

  	//Get the index for benchmarks
  	int benchmarkIndex = Utility::findSpecificPos("Benchmarks:", configs);

  	if (benchmarkIndex == -1)
  	{
  		std::cout << "ERROR: Please include a list of benchmarks to run with the like \"Benchmarks: test1.txt test2.txt\"" << std::endl;
  		exit(EXIT_FAILURE);
  	}

  	benchmarks = configs[benchmarkIndex];
  	configs.erase(configs.begin() + benchmarkIndex);
    int benchSize = benchmarks.size();

  	std::cout << "Generating All Configurations.";
    //PARALLEL
  	for (int i = 1; i < benchSize; i++)
  	{
      if (!Utility::exist(benchmarks[i]))
      {
        if (i == benchmarks.size() - 1)
        {
          exit(EXIT_FAILURE);
        }
        else
        {
          continue;
        }
      }

  		std::cout << ".";
      std::string benchmarkName;
      Utility::getBenchmarkName(benchmarks[i], benchmarkName);
  		std::string commandToMakeDir = "mkdir -p " + benchmarkName;

  		//SWAP COMMENTS FOR PRODUCTION
      system(commandToMakeDir.c_str());
  		std::string commands[2];
  		commands[0] = "";
  		commands[1] = "";

  		commands[0] = command;
  		commands[1] = " <" + benchmarks[i] + " 2>> ./DineroErrorLog.txt > ./" + benchmarkName + "/run";
  		CacheConfiguration newConfig;

  		buildConfigs( newConfig, commands[0], commands[1], 0);
  	}

  	std::cout << "Complete" << std::endl;

}
