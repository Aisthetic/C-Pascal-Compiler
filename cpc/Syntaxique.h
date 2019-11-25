#pragma once
#include "Lexical.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

class Syntaxique
{
public:
	// Constructeurs - Destructeurs
	Syntaxique();
	Syntaxique(Lexical* lexical);
	~Syntaxique();
	
	// Méthodes divers
	void startParsing();

	// Méthodes issues des productions
	void programme();
	void listeDeDeclarations();
	void declaration();
	void identificateur();
	void listeDeFonctions();
	void declarationFonction();
	void fonction();
	void listeDeParametres();
	void listeDInstructions();
	void constprime();
	void syntaxError(Production);
	void chiffre();
	void lettre();

	void consommer(char str);

	bool estPremierDe(Production unite);

	bool estSuivantDe(Production unite);

private:
	// Attributs	
	Lexical* lexical;
	TUniteLexicale uniteCourante;
	vector<string> errors;
	fstream xmlFile;

	// Methodes
	void end();
	void printErrors();
	void xmlOpen(string caller); // Ecrit dans le fichier XML la balise ouvrante de la fonction caller
	void xmlClose(string caller);  // De même pour la balise fermante
};

