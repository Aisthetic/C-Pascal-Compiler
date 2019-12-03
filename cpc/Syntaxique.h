#pragma once
#include "Lexical.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

class Syntaxique
{
public:
	// Constructeurs - Destructeurs
	Syntaxique(string inputFile);
	Syntaxique(Lexical* lexical);
	~Syntaxique();
	
	// M�thodes divers
	void startParsing();

private:
	// Attributs	
	Lexical* lexical;
	TUniteLexicale uniteCourante;
	vector<string> errors;
	ofstream xmlFile;

	// Methodes
	void end();
	void printErrors();
	void xmlOpen(string caller); // Ecrit dans le fichier XML la balise ouvrante de la fonction caller
	void xmlClose(string caller);  // De m�me pour la balise fermante$
	void syntaxError(Production prod);
	//void consommer();
	void consommer(string expected);//consomme en vérifiant si ul==expected
	bool estPremierDe(Production unite);
	bool estSuivantDe(Production unite);
	bool isMotCle(string mc); // voir si l'unite coutrante est mot cle egal au parametre entre 
	// M�thodes issues des productions
	void programme();
	void listeDeFonctions();
	void fonction();
	void listeDeDeclarations();
	void declarations();
	void declarationsPrime();
	void declaration();
	void declarationPrime();
	void declarationSeconde();
	void listeDeParametres();
	void parametres();
	void parametresPrime();
	void parametre();
	void listeInstructions();
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
	void parametresEffectifs();
	void expressions();
	void expressionsPrime();
	void operateurLogique();
	void comparaison();
	void identif();
	void cte();
};

