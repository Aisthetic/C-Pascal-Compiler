#include "Syntaxique.h"
#include "Lexical.h"
using namespace std;

//Constructeurs
Syntaxique::Syntaxique()
{
}

Syntaxique::Syntaxique(Lexical* pLexical)
{
	lexical = pLexical;
}

//Functions

/// <summary>
///	 Starts checking the syntax of the current file loaded in the lexical parser
/// </summary>
void Syntaxique::startParsing()
{
	// Gestion du fichier XML
	xmlFile.open("lexical.xml");
	xmlOpen("programme");
	consommer();
	programme();
	if (uniteCourante.UL == END) {
		xmlClose("programme");
		end(); //finish him!
	}
	else
		printErrors();	//affiche toutes les erreurs trouvées
}

void Syntaxique::end() {
	xmlFile.close();
}

void Syntaxique::printErrors() {

}

void Syntaxique::xmlOpen(string caller) {
	xmlFile << "<" << caller << ">";
}

void Syntaxique::xmlClose(string caller)
{
	xmlFile << "</" << caller << ">";
}
//Règles de grammaire
void Syntaxique::programme() {
	if (estPremierDe(eListeDeDeclarations)) {
		listeDeDeclarations();
		listeDeFonctions();
	}
	else {
		syntaxError(eProgramme);
	}
}
void Syntaxique::listeDeDeclarations() {
	if (estPremierDe(eDeclaration)) {
		declaration();
		consommer(',');//,
		listeDeDeclarations();
		consommer(';');
	}
	else if (estSuivantDe(eListeDeDeclarations)) {

	}
	else {
		syntaxError(eListeDeDeclarations);
	}
}
void Syntaxique::declaration() {

}
void Syntaxique::identificateur() {

}
void Syntaxique::listeDeFonctions() {
	if (estPremierDe(eFonction)) {
		fonction();
		listeDeFonctions();
	}
	else if (uniteCourante.UL == IDENT && uniteCourante.attribut==lexical->identifiants.existe("main")) {
		consommer('main');//main
		consommer('(');//(
		consommer(')');//)
		consommer('{');//{
		listeDInstructions();
		consommer('}');//}
	}
}
void Syntaxique::fonction() {
	if (estPremierDe(eIdentificateur)) {
		identificateur();
		consommer('(');//(
		listeDeParametres();
		consommer(')');//)
		listeDeDeclarations();
		consommer(';');//;
		consommer('}');//}
	}
}
void Syntaxique::listeDeParametres() {

}
void Syntaxique::listeDInstructions() {

}
void Syntaxique::constprime() {
	//if 
}

void Syntaxique::syntaxError(Production prod) {
	
}
void Syntaxique::chiffre() {
	if (uniteCourante.attribut >= '0' && uniteCourante.attribut <= '9') {
		xmlOpen("lettre");
		xmlFile << (char)uniteCourante.attribut;
		xmlClose("lettre");
		consommer(uniteCourante.attribut);
	}
	else {
		syntaxError(eCaractere);
	}

}

void Syntaxique::lettre() {
	if (((uniteCourante.attribut >= 'A' && uniteCourante.attribut <= 'Z') || (uniteCourante.attribut >= 'a' && uniteCourante.attribut <= 'z'))) {
		xmlOpen("lettre");
		xmlFile << (char)uniteCourante.attribut;
		xmlClose("lettre");
		consommer(uniteCourante.attribut);
	}
	else {
		syntaxError(eLettre);
	}
}

void Syntaxique::consommer(char str = ' ') {//nécessaire pour savoir ce qu'on a consommé (exemple lorsqu'on consomme le ;)
	uniteCourante = lexical->uniteSuivante();
}
//checks if the caracter is premier de l'unite en param
bool Syntaxique::estPremierDe(Production unite) {
	return false;
}

bool Syntaxique::estSuivantDe(Production unite) {
	return false;
}

//Destructeur
Syntaxique::~Syntaxique()
{
}