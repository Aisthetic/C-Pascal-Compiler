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
	void listeDeFonctions();
	void fonction();
	void listeDeDeclarations();
	void declarations();
	void declarationsPrime();
	void declaration();
	void declarationPrime();
	void declarationSeconde();
	void listeParametres();
	void parametres();
	void parametresPrime();
	void parametre();
	void listeInscructions();
	void instruction();
	void instructionPrime();
	void instructionTriple();
	void instructionSeconde();
	void expression();
	void expressionPrime();
	void expressionLogique();
	void expressionLogiquePrime();
	void expressionSimple();
	void expressionSimplePrime();
	void terme();
	void termePrime();
	void termePrioritaire();
	void facteur();
	void facteurPrime();
	void parametresEffictifs();
	void expressions();
	void expressionsPrime();
	void operateurLogique();
	void comparaison();
	void identif();
	void mot();
	void cte();
	void ctePrime();
	void chiffre();
	void lettre();

	void syntaxError(Production prod);

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

