#include <vector>
#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include <climits>
#include <algorithm>

#include "Utility.h"
#include "ConfigAnalyzer.h"

std::vector<std::string> cacheLevelNames = { "Instruction", "Data", "Level 2", "Level 3"};
std::vector<std::string> cacheLevelTypes = { "Size", "BlockSize", "SubBlock Size", "Associativity", "Hit", "Miss", "Fetches", "Miss Rate"};

void ConfigAnalyzer::populateStoredConfigs(ConfigBuilder &builder)
{
  std::string line;
  std::ifstream inFile;

  std::regex reg("(l1-icache|l1-dcache|l2-ucache|l3-ucache)");
  int configSize = builder.builtConfigs.size();

  //PARALLEL
  for (int i = 0; i < configSize; i++) {

    std::vector<std::string> commandParts;
    Utility::split(builder.builtConfigs[i], ' ', commandParts);

    std::string fileName = commandParts.back();
    inFile.open(fileName.c_str());

    while (!inFile.eof())
    {
      getline(inFile, line);
      int j;

      if (!std::regex_match(line, reg))
        continue;

      std::string type = line;
      Utility::jumpLines(inFile, line, 3);

      std::vector<std::string> fetches;
      Utility::split(line, '\t', fetches);
      builder.storedConfigs[i].setCacheValue(type + "f", fetches[2]);

      Utility::jumpLines(inFile, line, 4);

      std::vector<std::string> missRates;
      Utility::split(line, '\t', missRates);

      builder.storedConfigs[i].setCacheValue(type + "m", missRates[1]);

    }

    builder.storedConfigs[i].calcCPI();
    // std::cout << "CPI: " << builder.storedConfigs[i].CPI << std::endl;
    // for (int j = 0; j < cacheLevelNames.size(); j++) {
    //   std::cout << cacheLevelNames[j] << std::endl;
    //   for (int k = 0; k < cacheLevelTypes.size(); k++) {
    //     std::cout << "\t" << cacheLevelTypes[k] << ": " << builder.storedConfigs[i].getValue(cacheLevelNames[j], cacheLevelTypes[k]) << std::endl;
    //   }
    // }
    // char a;
    // std::cin >> a;

    inFile.close();
    inFile.clear();
  }
}

void ConfigAnalyzer::buildBenchFiles(ConfigBuilder &builder)
{
  std::cout << "Building Benchnark Files.";

  system("mkdir -p Combined");
  int typeSize = cacheLevelTypes.size();
  int nameSize = cacheLevelNames.size();

  std::cout << ".";

  std::stringstream columnNames;
  if (builder.storedConfigs[0].CPI != INT_MAX)
    columnNames << "CPI\t";

  for (int i = 0; i < nameSize; i++) {
    std::string level = cacheLevelNames[i];

    std::cout << ".";

    columnNames << "|"    ;
    if (i < 2) {
      columnNames << "L1 ";
    }
    columnNames << cacheLevelNames[i] << ":\t";

    for (int j = 0; j < typeSize; j++) {
      if (builder.storedConfigs[0].getValue(level, cacheLevelTypes[j]) != -1) {
        columnNames << cacheLevelTypes[j] << '\t';
      }
    }
  }
  columnNames << std::endl;

  std::cout << ".";

  std::ofstream file;
  int benchSize = builder.benchmarks.size() - 1;
  int configsPerBenchmark = builder.storedConfigs.size() / benchSize;
  std::string benchmarkName;
  std::stringstream data;
  int configIndex = 0;
  std::streamsize dataSize = data.precision();

  std::cout << ".";

  //for each benchmark
  //PARALLEL
  for (int i = 0; i < benchSize; i++) {
    std::cout << ".";
    Utility::getBenchmarkName(builder.benchmarks[i + 1], benchmarkName);

    //Consolidate all of the configs for this given benchmark
    std::vector<CacheConfiguration> configs;
    std::vector<CacheConfiguration>::iterator it = configs.begin();
    int startIndex = i * configsPerBenchmark;
    int endIndex = (i + 1) * configsPerBenchmark;
    configs.insert(it, builder.storedConfigs.begin() + startIndex, builder.storedConfigs.begin() + endIndex);

    std::sort(configs.begin(), configs.end(), isLess);

    data << benchmarkName << std::endl;
    data << columnNames.str();

    //check each of its configurations
    for (int j = 0; j < configsPerBenchmark; j++) {
      data << configs[j].CPI << '\t';


      //For each Cache level
      for (int k = 0; k < nameSize; k++) {
        std::string level = cacheLevelNames[k];
        data << '\t';

        //for each of the types in a cache level
        for (int l = 0; l < typeSize; l++) {
          std::string type = cacheLevelTypes[l];
          double configValue = configs[j].getValue(level, type);

          if ( configValue != -1) {
            if (type == "Miss Rate")
              data << std::fixed;

            if (type == "Fetches")
              data.precision(16);

            data << configValue << '\t';

            data.unsetf(std::ios_base::fixed);
            data.precision(dataSize);
          }
        }
      }

      data << std::endl;
    }

    file.open("./Combined/" + benchmarkName + ".txt");
    file << data.str();
    file.close();
    file.flush();



    data.str(std::string());

  }

  std::cout << ".Complete" << std::endl;
}

bool ConfigAnalyzer::isLess(CacheConfiguration a, CacheConfiguration b) { return (a.CPI < b.CPI);}
