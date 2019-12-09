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
	vector<string> code;
	Memoire memoire;

public:

	void exInstr(); // Execute instruction
	void exnextInstr(); // Execute next instruction
	void codeFile(); // open file containing code
	Interpreter(); // Constructor
};

