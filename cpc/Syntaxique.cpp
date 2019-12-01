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
		printErrors();	//affiche toutes les erreurs trouv�es
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
//R�gles de grammaire
void Syntaxique::programme() {
	if (estPremierDe(eListeDeDeclarations)) {
		listeDeDeclarations();
		listeDeFonctions();
	}
	else {
		syntaxError(eProgramme);
	}
}

void Syntaxique::listeDeFonctions()
{
}
void Syntaxique::fonction()
{
}

void Syntaxique::listeDeDeclarations()
{
}

void Syntaxique::declarations()
{
}

void Syntaxique::declarationsPrime()
{
}

void Syntaxique::declaration()
{
}

void Syntaxique::declarationPrime()
{
}

void Syntaxique::declarationSeconde()
{
}

void Syntaxique::listeDeParametres()
{
}

void Syntaxique::parametres()
{
}

void Syntaxique::parametresPrime()
{
}

void Syntaxique::parametre()
{
}

void Syntaxique::listeInscructions()
{
}

void Syntaxique::instruction()
{
}

void Syntaxique::instructionPrime()
{
}

void Syntaxique::instructionTriple()
{
}

void Syntaxique::instructionSeconde()
{
}

void Syntaxique::expression()
{
}

void Syntaxique::expressionPrime()
{
}

void Syntaxique::expressionLogique()
{
}

void Syntaxique::expressionLogiquePrime()
{
}

void Syntaxique::expressionSimple()
{
}

void Syntaxique::expressionSimplePrime()
{
}

void Syntaxique::terme()
{
}

void Syntaxique::termePrime()
{
}

void Syntaxique::termePrioritaire()
{
}

void Syntaxique::facteur()
{
}

void Syntaxique::facteurPrime()
{
}

void Syntaxique::parametresEffictifs()
{
}

void Syntaxique::expressions()
{
}

void Syntaxique::expressionsPrime()
{
}

void Syntaxique::operateurLogique()
{
}

void Syntaxique::comparaison()
{
}

void Syntaxique::identif()
{
}

void Syntaxique::mot()
{
}

void Syntaxique::cte()
{
}

void Syntaxique::ctePrime()
{
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



void Syntaxique::consommer(char str = ' ') {//n�cessaire pour savoir ce qu'on a consomm� (exemple lorsqu'on consomme le ;)
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