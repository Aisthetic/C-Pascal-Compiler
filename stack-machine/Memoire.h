#pragma once

#include <string>
using namespace std;

class Memoire
{
private:
	// Memory
	string* cells;

	// Registers
	int co;
	int beg;
	int bel;
	int sp;

public:
	// Instructions
	void empc(int value);
	void empc(Car value); // empiler Car
	void empl(string adress);
	void depl(string adress);
	void empg(string adress);
	void depg(string adress);
	void empt(string adress); // to check if Tableau has to be implemented !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void dept(string adress); // same
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

