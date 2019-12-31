#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <string>
#include "Memoire.h"
#include "Process.h"
using namespace std;

class Interpreter
{
private:
	vector<string> code;
	Memoire * memoire;
	Process * process;
	string currentInstruction;
	vector<string> console;
	bool debugMode = false;
	bool firstLine = true;

public:
	void exInstr(); // Execute instruction
	void codeFile(string); // open file containing code
	Interpreter(string file); // Constructor

	// Presentation
	void drawCell(int num, string value);
	void endDrawing();
	void drawStack();
	void drawPConsoleLine(int line);
	void drawPConsole();
	void clearConsole();
};

