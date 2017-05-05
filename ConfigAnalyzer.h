#pragma once

#include "ConfigBuilder.h"

class ConfigAnalyzer
{
  static bool isLess(CacheConfiguration a, CacheConfiguration b);
public:
  static void populateStoredConfigs(ConfigBuilder &builder);
  static void buildBenchFiles(ConfigBuilder &builder);
};
