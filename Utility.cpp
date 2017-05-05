#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <omp.h>

#include "Utility.h"

bool Utility::isRange(std::string &value)
{
  if (strstr(value.c_str(), ":") == NULL) {
    return false;
  }

  return true;
}

void Utility::split(std::string &words, char delimiter, std::vector<std::string> &seglist)
{
  std::string segment;
  std::stringstream range(words);
  while (getline(range, segment, delimiter))
  {
    seglist.push_back(segment);
  }
}

int Utility::findSpecificPos(const std::string delimiter, std::vector<std::vector<std::string> > &configs)
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

void Utility::jumpLines(std::ifstream &file, std::string &line, int jump)
{
  for (int k = 0; k < jump; k++) {
    getline(file, line);
  }
}

bool Utility::exist(std::string filename)
{
  std::ifstream file(filename);
  if (!file.good()) {
    std::cout << "Error: Invalid file name/path : " << filename << '\n';
    return false;
  }
  return true;
}

void Utility::reverseString(std::string &s)
{
  std::reverse(s.begin(), s.end());
}

void Utility::getBenchmarkName(std::string &s, std::string &benchmarkName)
{
  std::vector<std::string> bench;
  Utility::split( s, '/', bench);
  Utility::split( bench[ bench.size() - 1], '.', bench);
  benchmarkName = bench[ bench.size() - 2];
}

int Utility::threadCount()
{
  int n = 0;
  #pragma omp parallel reduction(+:n)
  n += 1;
  return n;
}
