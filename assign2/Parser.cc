#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

struct Variable {
    string name;
    double value;
};

// this is to be able to look up a variable in our vector by name using find
bool operator==(const Variable& l, const string& r) {
    return l.name == r;
}

struct Memory {
    vector<string> instructions;
    unsigned position;
    vector<Variable> variables;
};


int parseFile(ifstream &in_file, Memory &sysmem) {
    while (!in_file.eof()) {
        string line;
        getline(in_file, line);
        if (line[0] == '!') // skip comments
            continue;
        if (line.length() == 0) // skip blank lines because i am getting blank line before eof somehow..
            continue;
        istringstream elems(line);

        string elem;
        elems >> elem;
        if (elem == "SET") {
            // add variable if it doesnt exist
            elems >> elem;
            if (find(sysmem.variables.begin(), sysmem.variables.end(), elem) == sysmem.variables.end()) {
                Variable var;
                var.name = elem;
                sysmem.variables.push_back(var);
            }
            // make sure we have the =
            elems >> elem;
            if (elem != "=") {
                cerr << "Error in SET experssion: " << line << endl;
                return -1;
            }
            // make sure we are assigned to int or valid variable
            elems >> elem;
            istringstream is_dub(elem);
            double d;
            if (!(is_dub >> d)) {
                // its not a double so check that we have that variable
                if (find(sysmem.variables.begin(), sysmem.variables.end(), elem) == sysmem.variables.end()) {
                    cerr << "Error: righthand variable does not exist: " << line << endl;
                    return -1;
                }
            }
            if (elems >> elem) {
                cerr << "Error: extra garbage after SET expression: " << line << endl;
                return -1;
            }
            sysmem.instructions.push_back(line); // add cuz its valid
        } else if (elem == "PRINT") {
            elems >> elem;
            if (find(sysmem.variables.begin(), sysmem.variables.end(), elem) != sysmem.variables.end()) {
                sysmem.instructions.push_back(line);
            } else {
                cerr << "Error: cannot PRINT variable that has not be instantiated: " << line << endl;
                return -1;
            }
            if (elems >> elem) {
                cerr << "Error: extra garbage after PRINT expression: " << line << endl;
                return -1;
            }
        } else {
            cerr << "Error: instruction " << elem << " does not exist: " << line << endl;
            return -1;
        }
    }
    return 0;
}


int runInstructions(Memory &sysmem) {
    for (sysmem.position = 0; sysmem.position < sysmem.instructions.size(); sysmem.position++) {
        istringstream line(sysmem.instructions[sysmem.position]);
        string elem;
        line >> elem;
        if (elem == "SET") {
            line >> elem;
            vector<Variable>::iterator changing_var = find(sysmem.variables.begin(), sysmem.variables.end(), elem);
            line >> elem; // skip over the equals
            line >> elem;
            istringstream is_dub(elem);
            double d;
            if (is_dub >> d) {
                changing_var->value = d;
            } else {
                vector<Variable>::iterator var_with_val = find(sysmem.variables.begin(), sysmem.variables.end(), elem);
                changing_var->value = var_with_val->value;
            }
        } else if (elem == "PRINT") {
            line >> elem;
            vector<Variable>::iterator printing_var = find(sysmem.variables.begin(), sysmem.variables.end(), elem);
            cout << printing_var->value << endl;
        }
    }
    return 0;
}


int main(int argc, char ** argv) {
    // open file and check for launching errors
    if (argc < 2) {
        cerr << "Error: No input file specified. Usage Parser <filename>" << endl;
        return -1;
    }
    ifstream in_file;
    in_file.open(argv[1]);
    if (!in_file) {
        cerr << "Error: File not able to be opened" << endl;
        return -1;
    }

    // check through file line by line
    Memory sysmem;
    if (parseFile(in_file, sysmem)) { // successful call returns 0
        cerr << "Error: execution failed while parsing file" << endl;
        return -1;
    }
    runInstructions(sysmem);
    return 0;
}
