#pragma once

#include <algorithm>
#include <string>
#include <array>
#include <vector>
#include "Constantes.h"

using namespace std;

class Memoire
{
private:
	// Constructor
	Memoire(vector<string> code);

	// Memory
	array<string, memorySize> cells;

	// Registers
	int co; // Adress of the current executed instruction
	int beg; // Adress of the first global variable
	int bel; // Adress of the local memory of a function
	int sp; // Adress of the cell right after the summit of the stack

public:
	// Instructions
	void empc(int value);
	void empc(char value); // empiler Car
	void empl(string adress);
	void depl(string adress);
	void empg(string adress);
	void depg(string adress);
	void empt(string adress);
	void dept(string adress);
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
	void saut(string address);
	void sivrai(string adress);
	void sifaux(string adress);
	void appel(string adress);
	void retour();
	void entree();
	void sortie();
	void pile(int number);
	void dup();
	void pop();
	void stop();
};

