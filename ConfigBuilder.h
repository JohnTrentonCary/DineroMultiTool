#pragma once
#include <vector>
#include <string>
#include <fstream>

#include "CacheConfiguration.h"

class ConfigBuilder
{
private:

  void buildConfigs(CacheConfiguration &currentConfig,
                  std::string &executeCommand,
                  std::string &benchmarkCommand,
                  int configPos);
  void buildExec(std::string &commands, const std::string &delimiter);

public:
  int threadLimit;
  std::string creationTime;

  ConfigBuilder();
  std::vector<std::vector<std::string> > configs;
  std::vector<CacheConfiguration> storedConfigs;
  std::vector<std::string> benchmarks;
  std::vector<std::string> builtConfigs;
  void processFile(std::ifstream &inFile);
  void constructConfigs();
};
