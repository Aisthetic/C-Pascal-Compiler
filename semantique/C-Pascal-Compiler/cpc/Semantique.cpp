#pragma once
#include "Lexical.h"
#include "Semantique.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Constructeurs
Semantique::Semantique()
{
	
}

Semantique::~Semantique()
{
}

//methodes

bool Semantique::AjouterTS(string current)
{										  
	if (TS.find(TS.begin(), TS.end(),current) != TS.end())
		return false;
	variable var;
	var.val = current;
	TS.push_back(var);
	return true;
}	

void Semantique::AfficherTS()
{
	cout << "- Le tableau des Symboles contient : " << endl;
	for (int i = 0; i < TS.size(); i++) {
		cout << "  -- La Valeur = " << TS[i].val <<" de type =" << TS[i].type << endl;
	}
}
void Semantique::ControlerTS()
{
	cout << "- Le tableau de Symboles conient des erreurs :";
	for (int i = 0; i < TS.size(); i++) {
		if (TS[i].type != "entier" || TS[i].type != "car")
			cout << "  -- La Valeur =" << TS[i].val << " n'est pas declare "  << endl;
	}
}
/*
void Semantique::TypeTS(int ini,string typ)
{
	for (int i = ini; i < TS.size(); i++) {
		TS[i].type = typ;
	}
}
*/
bool Semantique::VerifierTableau(string current)
{
	int it = TS.find(TS.begin(), TS.end(), current);
	return (TS[it].nb > 0);
}
