#pragma once

#include "Utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Constants.h"
#include "ConsoleHandler.h"
#include <algorithm>
using namespace std;

typedef struct variable
{
	string val;
	string type;
	int nb = 0;
	int local_global; /// indiquer si l'identif est local ou global
	bool estfct=false;
	vector<string> param;
} variable;

class Semantique
{
public:
	// Constructeurs - Destructeurs
	Semantique();
	~Semantique();

	//methodes
	void AjouterTS(string,string);
	string typeidentifTS (string);
	void AfficherTS();
	void ControlerTS();
	bool VerifierTableau(string);
	bool VerifierFonction(string, vector<string>);
	void paramFonctTS();
	void logError(string error);

//private:
	vector<variable> TS;
};
