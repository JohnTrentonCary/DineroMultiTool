#pragma once
#include "ThreadSafeQueue.h"
#include "QueueItem.h"
#include "ConfigBuilder.h"


class ConfigRunner
{
private:
  volatile bool isFinished = false;
  void BackgroundJob(std::vector<std::string> &configsToRun,
    ThreadSafeQueue<QueueItem> &safeQueue,
    int threadLimit);

public:
  void runConfigs(ConfigBuilder &builder);
  ConfigRunner();
};
