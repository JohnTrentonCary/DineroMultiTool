#include <unistd.h>                  /*  for sleep()  */
#include <ncurses.h>
#include <thread>
#include <mutex>
#include <stdio.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <omp.h>

#include "ConfigRunner.h"
#include "ThreadSafeQueue.h"
#include "QueueItem.h"
#include "Utility.h"

ConfigRunner::ConfigRunner(){};

void ConfigRunner::BackgroundJob(std::vector<std::string> &configsToRun,
  ThreadSafeQueue<QueueItem> &safeQueue, int threadLimit)
{
  int configSize = configsToRun.size();

  if (threadLimit != 0) {
    omp_set_dynamic(0);
    omp_set_num_threads(threadLimit);
  }

	#pragma omp parallel for
	for (int i = 0; i < configSize; i++) {
		QueueItem newItem;
		newItem.id = i;
		newItem.status = 2;
		safeQueue.Enqueue(newItem);

		//Swap these for PRODUCTION
		// usleep(50000);
		system(configsToRun[i].c_str());

		newItem.status = 3;
		safeQueue.Enqueue(newItem);
	}

	isFinished = true;
}

void ConfigRunner::runConfigs(ConfigBuilder &builder)
{
	WINDOW *mainwin;
	if ( (mainwin = initscr()) == NULL ) {
		fprintf(stderr, "Error initialising ncurses.\n");
		exit(EXIT_FAILURE);
	}

	int benchSize = builder.benchmarks.size() - 1;
	int totalConfigs = builder.builtConfigs.size();
	int configsPerBenchmark = totalConfigs / benchSize;
	int width = 50;

	if (configsPerBenchmark < width)
		width = configsPerBenchmark;

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);

	color_set(1, NULL);
	for (int i = 0; i < benchSize; i++) {
		std::string output;
    Utility::getBenchmarkName(builder.benchmarks[i + 1], output);
		int lenDif = width - output.length();

		if (lenDif < 0)
		{

			std::string out1 = output;
			out1.resize(width);
			mvaddstr( i + 1, 0, out1.c_str());

			color_set(4, NULL);

			std::string out2 = output;
      Utility::reverseString(out2);
      out2.resize(-lenDif);
      Utility::reverseString(out2);
			mvaddstr(i + 1, out1.length(), out2.c_str());

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
  std::thread BackgroundThread = std::thread(&ConfigRunner::BackgroundJob, this, std::ref(builder.builtConfigs), std::ref(safeQueue), builder.threadLimit);

	std::vector<int> progress(benchSize, 0);
	std::vector<int> complete(benchSize, 0);
	int simsComplete = 0;

	while (true)
	{
		QueueItem outValue;

		if (safeQueue.Dequeue(outValue))
		{
			color_set(4, NULL);
			std::string benchesCompleted = "Simulations Complete: " + std::to_string(simsComplete) + "/" + std::to_string(totalConfigs) + " | ";
			mvaddstr(0,0, benchesCompleted.c_str());

      std::string threadsRunning = "Threads Running: " + std::to_string(Utility::threadCount());
      mvaddstr(0, benchesCompleted.length(), threadsRunning.c_str());

			int benchIndex = (outValue.id / configsPerBenchmark);
			std::string temp;
      Utility::getBenchmarkName(builder.benchmarks[benchIndex + 1], temp);
			int value;

			if (outValue.status == 2)
			{
				progress[benchIndex] += 1;
				value = (progress[benchIndex] * width) / configsPerBenchmark;
			}
			else if (outValue.status == 3) {
				complete[benchIndex] += 1;
				value = (complete[benchIndex] * width) / configsPerBenchmark;
  			simsComplete +=1;
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

	sleep(1);
	/*  Clean up after ourselves  */

	delwin(mainwin);
	endwin();
	refresh();
}
