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

bool operator==(const Variable& l, const Variable& r) {
    return l.name == r.name;
}

struct Memory {
    vector<string> instructions;
    int position;
    vector<Variable> variables;
};


int parseFile(ifstream &in_file, Memory *sysmem) {
    while (!in_file.eof()) {
        string line;
        getline(in_file, line);
        if (line[0] == '!') // skip comments
            continue;
        if (line.length() == 0) // skip blank lines because i am getting blank line before eof somehow..
            continue;
        istringstream elems(line);
        // cout << line << endl;

        string elem;
        elems >> elem;
        if (elem == "SET") {
            // capture our var
            elems >> elem;
            Variable var;
            var.name = elem;
            // make we have the =
            elems >> elem;
            if (elem != "=") {
                cerr << "Error: no equal in SET experssion: " << line << endl;
                return -1;
            }
            // make sure we are assigned to int or valid variable
            elems >> elem;
            istringstream is_dub(elem);
            double d;
            if (!(is_dub >> d)) {
                // its not a double so check that we have the variable
                Variable var2;
                var2.name = elem;
                if (find(sysmem->variables.begin(), sysmem->variables.end(), var2) == sysmem->variables.end()) {
                    cerr << "Error: righthand variable does not exist: " << line << endl;
                    return -1;
                }
            }
            sysmem->instructions.push_back(line); // add cuz its valid
            // create variable if it does not yet exist
            if (find(sysmem->variables.begin(), sysmem->variables.end(), var) == sysmem->variables.end()) {
                sysmem->variables.push_back(var);
            }
        } else if (elem == "PRINT") {
            elems >> elem;
            Variable var;
            var.name = elem; // if the variable to be printed is in memory, push instruction, else error and exit
            if (find(sysmem->variables.begin(), sysmem->variables.end(), var) != sysmem->variables.end()) {
                sysmem->instructions.push_back(line);
            } else {
                cerr << "Error: cannot PRINT variable that has not be instantiated: " << line << endl;
                return -1;
            }
        } else {
            cerr << "Error: instruction " << elem << " does not exist: " << line << endl;
            return -1;
        }
    }
    return 0;
}


int runInstructions(Memory *sysmem) {
    for (; sysmem->position < sysmem->instructions.size(); sysmem->position++) {
        istringstream line(sysmem->instructions[sysmem->position]);
        string elem;
        line >> elem;
        if (elem == "SET") {
            Variable var;
            line >> var.name;
            vector<Variable>::iterator changing_var = find(sysmem->variables.begin(), sysmem->variables.end(), var);
            line >> elem; // skip over the equals
            line >> elem;
            istringstream is_dub(elem);
            double d;
            if (is_dub >> d) {
                changing_var->value = d;
                cout << changing_var->name << " set to " << d << endl;
            } else {
                Variable var2;
                var2.name = elem;
                vector<Variable>::iterator var_with_val = find(sysmem->variables.begin(), sysmem->variables.end(), var2);
                changing_var->value = var_with_val->value;
                cout << changing_var->name << " set to " << var_with_val->value << endl;
            }
        } else if (elem == "PRINT") {
            line >> elem;
            Variable var;
            var.name = elem; // if the variable to be printed is in memory, push instruction, else error and exit
            vector<Variable>::iterator printing_var = find(sysmem->variables.begin(), sysmem->variables.end(), var);
            cout << printing_var->value << endl;
        }
    }
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
    Memory *sysmem = new Memory;
    if (parseFile(in_file, sysmem)) { // successful call returns 0
        cerr << "Error: execution failed while parsing file" << endl;
        return -1;
    }
    runInstructions(sysmem);
    return 0;
}
