#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <cmath>

using namespace std;

bool isRange(string value)
{
  if (strstr(value.c_str(), ":") == NULL) {
    return false;
  }

  return true;
}

vector<string> split(string words, char delimiter)
{
  string segment;
  stringstream range(words);
  vector<string> seglist;
  while (getline(range, segment, delimiter))
  {
    seglist.push_back(segment);
  }

  return seglist;
}

string getFlag(string designator)
{
  if ("Benchmarks")
  {
    return "<";
  }
  return NULL;
}

void buildExec(vector< vector<string> > &configs, string &commands, string delimiter)
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

int findSpecificPos(vector< vector<string> > &configs, string delimiter)
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

void buildConfigs(vector< vector< string> > configs, 
  int configPos, 
  string command[])
{
  if (configPos == configs.size() - 1)
  {
    //Base case
  }
  else
  {

  }
}

vector< vector<string> > processFile(ifstream &inFile)
{
  string line;
  vector< vector<string> > configs;
  while (!inFile.eof()) {
    getline(inFile, line);

    //Make sure the line isn't blank
    if (line.length() == 0)
      continue;

    //Split the line up into its parts
    vector< string> newConfigSet = split(line, ' ');

    //Check if any nodes have a range
    for (int i = 1; i < newConfigSet.size(); i++) {

      if (isRange(newConfigSet[i])) {
        vector<string> ranges = split(newConfigSet[i], ':');
        vector<string>::iterator currentPos = newConfigSet.begin() + i + 1;
        newConfigSet.insert(currentPos, ranges.begin(), ranges.end());
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
        realValue = pow(2, realValue);
        newConfigSet[i] = to_string(realValue);
      }
    }

    //for (int i = 0; i < newConfigSet.size(); i++) {
    //  cout << newConfigSet[i] << endl;
    //}
    //cin >> line;


    configs.push_back(newConfigSet);
  }

  return configs;
}

int main(int argc, char const *argv[])
{

  if (argc == 1) {
    cout << "Please include a Dinero MultiConfigurations file" << endl;
    return 0;
  }

  cout << "Opening File.";

  ifstream inFile;
  inFile.open(argv[1]);

  cout << "..........Complete\n";

  //Get all of the data into the 2D vector
  vector< vector<string> > configs = processFile(inFile);

  
  string command = "";
  buildExec(configs, command, "DineroLocation:");
  command += " $cfgs <";
  
  int benchmarks = findSpecificPos(configs, "Benchmarks:");

  if (benchmarks == -1)
  {
    cout << "ERROR: Please include a list of benchmarks to run with the like \"Benchmarks: test1.txt test2.txt\"" << endl;
    return 0;
  }

  for (int i = 1; i < configs[benchmarks].size(); i++)
  {
    vector<string> bench = split(configs[benchmarks][i], '/');
    bench = split(bench[bench.size() - 1], '.');
    string directoryToSaveTo = bench[bench.size() - 2];
    string commandToMakeDir = "mkdir -p " + directoryToSaveTo;
    system(commandToMakeDir.c_str());

    string commands[2] = { "cfgs=\"", "" };
    string currentBenchmark = configs[benchmarks][i];
    commands[1] = command + currentBenchmark + " > ~/" + currentBenchmark + "/";
    
    buildConfigs(configs, 1, commands);
  }
  

  // cout << "Collecting File information.";

  return 0;
}
