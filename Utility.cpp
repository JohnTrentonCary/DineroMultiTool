#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <omp.h>
#include <climits>
#include <ctime>

#include "Utility.h"

bool Utility::isRange(std::string &value)
{
  if (strstr(value.c_str(), ":") == NULL) {
    return false;
  }
  else if (value.front() == ':' || value.back() == ':')
  {
    std::cout << "Error: Invalid range: " << value << '\n';
    exit(EXIT_FAILURE);
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
    std::cout << "Error: Invalid file name/path : " << filename << std::endl;
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

bool Utility::isPowerOf2(const int value)
{
  if((value & (value - 1)) == 0)
    return true;

  return false;
}

bool Utility::isInt(const char *s)
{
  if (s == nullptr || s[0] == '\0')
        return false;

  char* end = nullptr;
  errno = 0;
  strtol(s, &end, 10);

  if (errno != 0)
      return false;

  return (end != nullptr && *end == '\0');
}

std::string Utility::getTime()
{
  char timeStr[80];
  std::time_t rawTime;
  struct tm * sysTime;

  std::time(&rawTime);
  sysTime = localtime(&rawTime);
  std::strftime(timeStr, 80, "%y%m%d%H%M%S", sysTime);
  return timeStr;
}
