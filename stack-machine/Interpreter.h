#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include "Memoire.h"
using namespace std;

class Interpreter
{
private:
	string inputFile; // File contain code
	ifstream input;//peut être fichier,string dans la console..
	std::vector<string> code;
	ofstream output;
	Memoire memoire;
public:
	string nextInstr(); // Returns next instruction
	void exInstr(); // Execute next instruction
	void codeFile(); // open file containing code
	Interpreter(); // Constructor
};

