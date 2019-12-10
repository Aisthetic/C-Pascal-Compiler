#pragma once

#include <iostream>
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
	vector<string> code;
	Memoire * memoire;
	string currentInstruction;

public:
	void exInstr(); // Execute instruction
	void codeFile(string); // open file containing code
	Interpreter(string file); // Constructor
};

