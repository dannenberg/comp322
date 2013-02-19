#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

struct Variable
{
  string name;
  double value;
};

struct Memory
{
  vector<string> instructions;
  int position;
  vector<Variable> variables;
};


int main(int argc, char ** argv) {
  if (argc < 2)
  {
    cerr << "Error: No input file specified. Usage Parser <filename>" << endl;
    return 1;
  }

  ifstream in_file;
  in_file.open(argv[1]);
  if (!in_file)
  {
    cerr << "Error: File not able to be opened" << endl;
    return 1;
  }

  //parse the file and execute the instructions here!
  return 0;
}

