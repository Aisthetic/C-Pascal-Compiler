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
	array<string, memorySize> cells;

	// Registers
	int co = 0; // Adress of the current executed instruction
	int beg = 0; // Adress of the first global variable
	int bel = 0; // Adress of the local memory of a function
	int sp = 0; // Adress of the cell right after the summit of the stack

public:
	// Constructor
	Memoire(vector<string> code);

	// Utilities
	bool stackFull(); // Check if the stack is full
	bool stackEmpty(); // Check if the stack is empty

	// Instructions
	void empc(string value);
	void empl(int adress);
	void depl(int adress);
	void empg(int adress);
	void depg(int adress);
	void empt(int adress);
	void dept(int adress);
	void addi(); // Can't use add because it's taken by c++
	void sous();
	void mul();
	void div();
	void mod();
	void egal();
	void inf();
	void infeg();
	void non();
	void lire();
	void ecriv();
	void saut(int address);
	void sivrai(int adress);
	void sifaux(int adress);
	void appel(int adress);
	void retour();
	void entree();
	void sortie();
	void pile(int number);
	void dup();
	void pop();
	void stop();


	// Getters
	int getCo();
	string getCell(int num);

	// Setters
	void incCo();
	void setCo(int toSet);
};

