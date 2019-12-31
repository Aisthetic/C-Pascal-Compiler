#pragma once
#include "Lexical.h"
#include "Semantique.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Constructeurs
Semantique::Semantique() :SementicTable('-', '|', '+')
{
	setupTSOutput();
	//Initializing members
	SementicTable.add("Valeur d'identifiant");
	SementicTable.add("est_elle fonction");
	SementicTable.add("Type");
	SementicTable.add("Scope");
	SementicTable.endOfRow();

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

//void Semantique::AfficherTS()
//{
//	cout << "- Le tableau des Symboles contient : " << endl;
//	for (int i = 0; i < TS.size(); i++) {
//		cout << "  -- La Valeur = " << TS[i].nom << " , est-elle une fonction = " << TS[i].estfct << ", de type = " << TS[i].type << ", dans le scope = " << TS[i].scope << endl;
//	}
//}
void Semantique::AfficherTS()
{
	cout << "TS table will be logged at ./Output/Semantique/TS_Table.txt" << endl;
	for (int i = 0; i < TS.size(); i++) {
		//cout << "  -- La Valeur = " << TS[i].nom << " , est-elle une fonction = " << TS[i].estfct << ", de type = " << TS[i].type << ", dans le scope = " << TS[i].scope << endl;
		SementicTable.add(TS[i].nom);
		SementicTable.add(to_string(TS[i].estfct));
		SementicTable.add(TS[i].type);
		SementicTable.add(to_string(TS[i].scope));
		SementicTable.endOfRow();
	}

	TSOutput << SementicTable;
}

void Semantique::ControlerTS()
{
	AfficherTS();
	cout << "- Le tableau de Symboles contient des erreurs :\n";
	for (int i = 0; i < TS.size(); i++) {
		if (TS[i].type != "entier" && TS[i].type != "car" && TS[i].estfct != true)
			cout << "  -- La Valeur = " << TS[i].nom << " n'est pas declare " << endl;

		for (int j = i + 1; j < TS.size(); j++) {
			if (TS[i].nom == TS[j].nom && TS[i].estfct == TS[j].estfct && TS[i].param.size() == TS[j].param.size() && TS[i].scope == TS[j].scope)
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

	while (TS[functionPostion].estfct != true)
		functionPostion--;
		
	for (int i = TS.size() - 1; TS[i].estfct != true; i--) {
		TS[functionPostion].param.insert(TS[functionPostion].param.begin(),TS[i]);
	}
}

void Semantique::logError(string error)
{
	ConsoleHandler::logError("Semantique", error);
}

//Zac's precious functions

variable Semantique::getVariableData(string name, int scope)
{
	for (int i = TS.size() - 1; i > -1 ; i--) // we start by looking for local vars since they're at the end of the table
		if (TS[i].nom == name && (TS[i].scope == scope || TS[i].scope == 0 || TS[i].param.size() > 0)) // functions are not affected by this scope
			return TS[i];																				//thingie
	logError("variable " + name + "'s data not found.");
	return variable{};
}

int Semantique::getVariableAddress(string name, int scope)
{
	//L'adresse d'une variable equivaut a son ordre de declaration
	//on va donc chercher son ordre de declaration dans son scope
	variable data = getVariableData(name, scope);

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
			if (variable.estfct == true && variable.scope == data.scope) {
				containingFunction = &variable;
			}
		}

		if (containingFunction == NULL)
		{
			logError("Couldn't find containing function for variable " + name);
			return -1;
		}
		else // on ne compte pas la fonction elle même d'où le -1, l
		 declarationsNumberCount = declarationsNumberCount - 1 - containingFunction->param.size(); 

		//Si notre variable est un parametre
		int paramCount = 0;
		for (int i = containingFunction->param.size() - 1; i >= 0; i--) {
			auto param = containingFunction->param[i];
			if (param.nom == data.nom) {
				return  - paramCount - 3; // on se deplace sous sous le BEL
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

//Cree un fichier d'output 
void Semantique::setupTSOutput() {
	if (!TSOutput.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		TSOutput.open(SEMANTIQUE_OUTPUT_DIRECTORY + "/TS_Table.txt");
		if (!TSOutput.is_open()) {
			logError("Impossible d'ouvrir le fichier d'TSOutput");
			return;
		}
	}
}