#include <string>
#include <fstream>
#include <vector>

class Utility
{
public:
  static bool isRange(std::string &value);
  static void split(std::string &words,
    char delimiter,
    std::vector<std::string> &seglist);
  static int findSpecificPos(const std::string delimiter,
    std::vector<std::vector<std::string> > &configs);
  static void jumpLines(std::ifstream &file, std::string &line, int jump);
  static bool exist(std::string filename);
  static void reverseString(std::string &s);
  static void getBenchmarkName(std::string &s, std::string &benchmarkName);
  static int threadCount();
  static bool isPowerOf2(const int value);
  static bool isInt(const char *s);
};
