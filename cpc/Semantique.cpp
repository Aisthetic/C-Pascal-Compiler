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

void Semantique::AjouterTS(string cas, string current, int ite_varlocalglobal)
{
	variable var;
	if (cas == "type")
		var.type = current;
	if (cas == "val")
		var.nom = current;
	var.scope = ite_varlocalglobal;
	TS.push_back(var);
}

string Semantique::typeidentifTS(string nom)
{
	for (int i = 0; i < TS.size(); i++)
		if (TS[i].nom == nom)
			return TS[i].type;
}

void Semantique::AfficherTS()
{
	cout << "- Le tableau des Symboles contient : " << endl;
	for (int i = 0; i < TS.size(); i++) {
		cout << "  -- La Valeur = " << TS[i].nom << ", de type = " << TS[i].type << ", dans le scope = " << TS[i].scope << endl;
	}
}

void Semantique::ControlerTS()
{
	AfficherTS();
	cout << "- Le tableau de Symboles contient des erreurs :\n";
	for (int i = 0; i < TS.size(); i++) {
		if (TS[i].type != "entier" && TS[i].type != "car" && TS[i].type != "fct")
			cout << "  -- La Valeur = " << TS[i].nom << " n'est pas declare " << endl;

		for (int j = i + 1; j < TS.size(); j++) {
			if (TS[i].nom == TS[j].nom && TS[i].type == "fct" && TS[j].type == "fct" && TS[i].param.size() == TS[j].param.size() && TS[i].scope == TS[j].scope)
				cout << "  -- La Valeur = " << TS[i].nom << " est repetee " << endl;
		}
	}
}

bool Semantique::VerifierTableau(string current)
{
	for (int i = 0; i < TS.size(); i++)
		if (TS[i].nom == current)
			return (TS[i].nb > 0);
	return false;
}

bool Semantique::VerifierFonction(string current, vector<string> paramtr)
{
	for (int i = 0; i < TS.size(); i++)
		if (TS[i].nom == current) {
			for (int j = 0; j < TS[i].param.size(); j++)
				if (TS[i].param[j].type != paramtr[j])
					return false;
		}
			
	return true;
}

void Semantique::paramFonctTS()
{
	vector<variable> listeparam;
	int functionPostion = TS.size() - 1;

	while (TS[functionPostion].type != "fct")
		functionPostion--;
		
	for (int i = TS.size() - 1; TS[i].type != "fct"; i--) {
		TS[functionPostion].param.insert(TS[functionPostion].param.begin(),TS[i]);
	}
}

void Semantique::logError(string error)
{
	ConsoleHandler::logError("Semantique", error);
}

//Zac's precious functions

variable Semantique::getVariableData(string name)
{
	for (int i = TS.size() - 1; i > -1 ; i--) // local over global
		if (TS[i].nom == name)
			return TS[i];
	logError("variable " + name + "'s data not found.");
	return variable{};
}

int Semantique::getVariableAddress(string name)
{
	//L'adresse d'une variable equivaut a son ordre de declaration
	//on va donc chercher son ordre de declaration dans son scope
	variable data = getVariableData(name);

	if (data.scope == 0) {//variable globle ez pez
		int declarationsNumberCount = 0;
		for (int i = 0; i < TS.size(); i++) {
			if (TS[i].scope == 0) {
				if (TS[i].nom == name)
					return declarationsNumberCount;
				declarationsNumberCount++;
			}
		}				
	}
	else { //variable local, note: this can be optimized but it's more lisible this way

		variable* containingFunction = NULL;
		int declarationsNumberCount = 0;

		for (auto & variable : TS) {// on cherche les inforamation de la fonction contenant notre variable
			if (variable.type == "fct" && variable.scope == data.scope) {
				containingFunction = &variable;
			}
		}

		if (containingFunction == NULL)
		{
			logError("Couldn't find containing function for variable " + name);
			return -1;
		}
		else // on ne compte pas la fonction elle même d'où le -1
			//puis on ajoute l' offset des autres variables dans la pile
			// l'offset = 3 est celui du resultat + BEL Precedent + addr de retours
		 declarationsNumberCount = declarationsNumberCount - 1 + 3; 

		//Si notre variable est un parametre
		int paramCount = 0;
		for (auto const& param : containingFunction->param) {
			if (param.nom == data.nom) {
				return 3 + paramCount;
			}
			paramCount++;
		}

		//Si notre varialbe est une variable locale
		for (int i = 0; i < TS.size(); i++) {
			if (TS[i].scope == containingFunction->scope) {
				if (TS[i].nom == name)
					return declarationsNumberCount;
				declarationsNumberCount++;
			}
		}
	}
	return -1;
}
