#pragma once

#include <string>
#include "Memoire.h"
using namespace std;

class Interpreter
{
private:
	string inputFile; // File contain code
	Memoire memoire;
public:
	string nextInstr(); // Returns next instruction
	void exInstr(); // Execute next instruction
	Interpreter(); // Constructor
};

