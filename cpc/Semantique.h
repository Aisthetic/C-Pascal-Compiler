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

typedef struct variable // structure pour stocker les infos d'une variable
{
	string nom; //Nom de la variable
	string type;
	int nb = 0; // differencie entre tableau et var smple
	int scope; // indiquer si l'identif est local ou global (zac : plutot son scope ?)
	vector<variable> param; //stocke les parameteres de la fct
} variable;

class Semantique
{
public:
	// Constructeurs - Destructeurs
	Semantique();
	~Semantique();

	//methodes
	void AjouterTS(string nom,string dans_quelle_cas_var_on_ajoute,int); // crée une variable et l'ajout au TS
	string typeidentifTS (string); // retourne le type de l'identif a partir TS
	void AfficherTS();  // affiche le contenu de TS
	void ControlerTS(); // controle TS vers la fin du l'analyse pour en sortir les variables non déclarer
	bool VerifierTableau(string); // verifie si l'identif est un tableau en TS
	bool VerifierFonction(string, vector<string>); // verifier si l'identif est une fct en TS
	void paramFonctTS();		  // identifie des identifiants comme etant des parametres d'une fct 
	void logError(string error); // afficher les erreurs du semantique
	variable getVariableData(string name, int scope);
	int getVariableAddress(string name, int scope);//retruns the variable address in its decalaration scope
//private:
	vector<variable> TS; /// tableau des variables
};
