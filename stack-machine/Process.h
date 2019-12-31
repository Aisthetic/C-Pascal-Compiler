#pragma once

#include "Memoire.h"

class Process
{
private:
	// Memory
	Memoire * memoire;

public:
	// Constructor
	Process(Memoire * mem);

	// Instructions
	void empc(string value);
	void empl(int address);
	void depl(int address);
	void empg(int address);
	void depg(int address);
	void empt(int address);
	void dept(int address);
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
	string ecriv();
	void saut(int address);
	void sivrai(int address);
	void sifaux(int address);
	void appel(int address);
	void retour();
	void entree();
	void sortie();
	void pile(int number);
	void dup();
	void pop();
	void stop();

	string dep();
	void emp(string value);
};

