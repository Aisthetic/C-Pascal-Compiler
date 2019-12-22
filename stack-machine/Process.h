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

	string dep();
	void emp(string value);
};

