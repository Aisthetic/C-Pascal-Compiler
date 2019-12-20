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

void Semantique::AjouterTS(string cas,string current,int ite_varlocalglobal)
{
	variable var;
	if (cas=="type")
		var.type = current;
	if (cas=="val")
		var.val = current;
	var.local_global = ite_varlocalglobal;
	TS.push_back(var);
}

string Semantique::typeidentifTS(string nom)
{
	for (int i = 0; i < TS.size(); i++)
		if (TS[i].val == nom)
			return TS[i].type;
}

void Semantique::AfficherTS()
{
	cout << "- Le tableau des Symboles contient : " << endl;
	for (int i = 0; i < TS.size(); i++) {
		cout << "  -- La Valeur = " << TS[i].val << " , est-elle une fonction = " << TS[i].estfct <<", de type = " << TS[i].type << endl;
	}
}

void Semantique::ControlerTS()
{
	AfficherTS();
	cout << "- Le tableau de Symboles contient des erreurs :\n";
	for (int i = 0; i < TS.size(); i++) {
		if (TS[i].type != "entier" && TS[i].type != "car" && TS[i].estfct != true )
			cout << "  -- La Valeur = " << TS[i].val << " n'est pas declare " << endl;

		for (int j = i + 1; j < TS.size(); j++) {
			if (TS[i].val == TS[j].val  && TS[i].estfct == TS[j].estfct && TS[i].param == TS[j].param && TS[i].local_global == TS[j].local_global)
				cout << "  -- La Valeur = " << TS[i].val << " est repetee " << endl;
		}
	}
}

bool Semantique::VerifierTableau(string current)
{
	for (int i = 0; i < TS.size(); i++) 
		if (TS[i].val == current)
			return (TS[i].nb > 0);
	return false;
}

bool Semantique::VerifierFonction(string current, vector<string> paramtr)
{
	for (int i = 0; i < TS.size(); i++)
		if (TS[i].val == current)
			return TS[i].param == paramtr;
	return false;
}

void Semantique::paramFonctTS()
{
	vector<string> listeparam;
	int i;
	for (i = TS.size()-1; TS[i].estfct != true; i--) {
		listeparam.insert(listeparam.begin(),TS[i].type);
	}
	TS[i].param = listeparam;
}

void Semantique::logError(string error)
{
	ConsoleHandler::logError("Semantique", error);
}
