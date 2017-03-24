#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>

using namespace std;

bool isRange(string value)
{
  if (strstr( value.c_str(), ":") == NULL) {
    return false;
  }

  return true;
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



  string word;
  vector< vector<string> > configs;

 // cout << "Collecting File information.";

  while (!inFile.eof()) {
    inFile >> word;

    char * temp;
    if ( !strtol( word.c_str(), &temp, 10)) {

      vector<string> newSet;

      configs.push_back(newSet);
    }
    else if (isRange(word)) {

      string segment;
      stringstream range(word);
      vector<string> seglist;
      while(getline( range, segment, ':'))
      {
         seglist.push_back(segment);
      }

      int min = stoi(seglist[0]);
      int max = stoi(seglist[1]);

      if (min > max) {
        cout << "ERROR: min of the specified range is greater than the max for: " << word << endl;
        return 0;
      }

      for (int i = min; i < max; i++) {
        configs[configs.size()-1].push_back(to_string(i));
      }

      word = "";
    }

    int lastEle = configs.size() -1;

    if (word != "")
      configs[ lastEle].push_back(word);

  }

  for (int i = 0; i < configs.size(); i++) {
    for (int j = 0; j < configs[i].size(); j++) {
      if (j > 0) {
        cout << "\t";
      }
      cout << configs[i][j] << endl;
    }
  }

  return 0;
}
