#pragma once

#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include "Constantes.h"

using namespace std;

class Memoire
{
private:

	// Memory
	array<string, MEMORYSIZE> cells;

	// Registers
	int co = 0; // address of the current executed instruction
	int beg = 0; // address of the first global variable
	int bel = 0; // address of the local memory of a function
	int sp = 0; // address of the cell right after the summit of the stack

	// Global variables
	int varGloNum = 0;

public:
	// Constructor
	Memoire(vector<string> code);

	// Utilities
	bool stackFull(); // Check if the stack is full
	bool stackEmpty(); // Check if the stack is empty

	// Getters
	int getCo();
	int getBeg();
	int getBel();
	int getSp();
	string getCell(int num);
	int getStCellNum(int cell);
	int getVarGloNum();

	// Setters
	void incCo();
	void incSp();
	void decSp();
	void incVarGloNum();
	void setCo(int toSet);
	void setBel(int toSet);
	void setSp(int toSet);
	void setCell(int num, string value);
};

