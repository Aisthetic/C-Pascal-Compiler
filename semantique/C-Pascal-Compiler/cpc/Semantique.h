#pragma once

#include "Utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

typedef struct variable
{
	string val;
	string type;
	int nb=0;
} variable;

class Semantique
{
public:
	// Constructeurs - Destructeurs
	Semantique();
	~Semantique();
	
	//methodes
	bool AjouterTS(string);
	void AfficherTS();
	void ControlerTS();
	bool VerifierTableau(string);
	//void TypeTS(int ini, string typ);
//private:
	vector<variable> TS;
};
