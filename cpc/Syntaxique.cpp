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
	if (estPremierDe(eFonction))
	{
		consommer();
		fonction();
		consommer();
		listeDeDeclarations();
	}
	else if (uniteCourante.UL== MOTCLE &&uniteCourante.UL == lexical->identifiants.existe("main")) // à affiner
	{
		consommer();
		consommer('{');
		listeInscructions();
		consommer('}');
	}
	else
	{
		syntaxError(eFonction);
	}
}
void Syntaxique::fonction()
{
	if (estPremierDe(eIdentificateur))
	{
		consommer();
		consommer('(');
		listeDeParametres();
		consommer(')');
		listeDeDeclarations();
		consommer('{');
		listeInscructions();
		consommer('}');
	}
	else
	{
		syntaxError(eIdentificateur);
	}

}

void Syntaxique::listeDeDeclarations()
{
	if (estPremierDe(eDeclaration))
	{
		consommer();
		declarations();
	}
	else
	{
		syntaxError(eDeclaration);
	}
}

void Syntaxique::declarations()
{
	if (estPremierDe(eDeclaration))
	{
		declaration();
		declarationPrime();
	}
	else {
		syntaxError(eDeclaration);
	}
}

void Syntaxique::declarationsPrime()
{
	if(estPremierDe(eDeclaration))
	{
		consommer(',');
		declaration();
		declarationsPrime();
	}
	else {
		syntaxError(eListeDeDeclarationsPrime);
	}
}

void Syntaxique::declaration()
{
	if (uniteCourante.UL == MOTCLE && uniteCourante.UL == lexical->identifiants.existe("entier"))
	{
		consommer();
		declarationPrime();
	}
	else if (uniteCourante.UL == MOTCLE && uniteCourante.UL == lexical->identifiants.existe("car"))
	{
		consommer();
		declarationPrime();
	}
	else
	{
		syntaxError(eDeclaration);
	}
}

void Syntaxique::declarationPrime()
{
	if (estPremierDe(eIdentificateur))
	{
		consommer();
		declarationSeconde();
	}
	else {
		syntaxError(eDeclaration);
	}
}

void Syntaxique::declarationSeconde()
{
	if (estPremierDe(eExpression))
	{
		consommer();
		expression();
	}
}

void Syntaxique::listeDeParametres()
{
	if (estPremierDe(eParametre))
	{
		consommer();
		parametre();
	}
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

void Syntaxique::expressionLogique(){
	if (estPremierDe(eexpressionSimple)) {
		expressionSimple();
		expressionLogiquePrime();
	}
	else {
		syntaxError(eexpressionLogique);
	}
}

void Syntaxique::expressionLogiquePrime(){
	if (estPremierDe(ecomparaison)) {
		comparaison();
		expressionSimple();
		expressionLogiquePrime();
	}
}

void Syntaxique::expressionSimple(){
	if (estPremierDe(eterme)) {
		terme();
		expressionSimplePrime();
	}
	else if(uniteCourante.UL == "SOUS" ){
        consommer(); 
		terme();
		expressionSimplePrime();
	}
	else {
		syntaxError(eexpressionSimple);
	}
}

void Syntaxique::expressionSimplePrime(){
	if (uniteCourante.UL == "ADD") {
		consommer();
		terme();
		expressionSimplePrime();
	}
	else if(uniteCourante.UL == "SOUS" ) {
		consommer();
		terme();
		expressionSimplePrime();
	}
}

void Syntaxique::terme(){
	if (estPremierDe(etermePrioritaire)) {
		termePrioritaire();
		termePrime();
	}
	else {
		syntaxError(eterme);
	}
}
void Syntaxique::termePrime(){
	if (uniteCourante.UL == "MUL") {
		consommer();
		facteur();
		termePrime();
	}
	else if (uniteCourante.UL == "DIV" ) {
		consommer();
		facteur();
		termePrime();
	}
}

void Syntaxique::termePrioritaire(){
	if (uniteCourante.UL == "NON") {
		consommer();
		facteur();
	}
	else if (estPremierDe(efacteur) ) {
		facteur();
	}
	else {
		syntaxError(etermePrioritaire);
	}
}

void Syntaxique::facteur(){
	if (estPremierDe(eidentif)) {
		identif();
		facteurPrime();
	}
	else if(estPremierDe(ecte)){
		cte();
	}
	else if (uniteCourante.UL == "PAROUV" ) {
		consommer();
		expression();
	    //// souhail : il faut ajouter une condition ici ==> verifier_unite(PARFER) 
	}
	else if(uniteCourante.UL == ""){ //souhail : ****** ajouter ' au lexical UL
        consommer(); 
		lettre();
		//// souhail : il faut ajouter une condition ici ==> verifier_unite(TIRÉ) 
	}
	else {
		syntaxError(eFacteur);
	}
}
	
void Syntaxique::facteurPrime(){
	if (uniteCourante.UL == CROOUV) {
		consommer();
		expression();
		//// souhail : il faut ajouter une condition ici ==> verifier_unite(COUVFER) 
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer();
		parametresEffictifs();
		//// souhail : il faut ajouter une condition ici ==> verifier_unite(PARFER) 
	}
}
void Syntaxique::parametresEffictifs(){
	if (estPremierDe(eExpressions)) {
		expressions(); 
	}
}

void Syntaxique::expressions()
{
	if(estPremierDe(eExpression)){
		expression();
		expressionPrime();
	}
	else {
		syntaxError(eExpression);
	}
}

void Syntaxique::expressionsPrime()
{
	if (uniteCourante.UL == VIRG) {
		expression();
		expressionPrime();
	}
	else if (estSuivantDe(eExpressionPrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eExpression);
	}
}

void Syntaxique::operateurLogique()
{
	if (uniteCourante.UL == OU || uniteCourante.UL == ET) {
		consommer();
	}
	else {
		syntaxError(eOperateurLogique);
	}
}

void Syntaxique::comparaison()
{
	if (uniteCourante.UL == SUP || uniteCourante.UL == INFEGAL || uniteCourante.UL == SUPEGAL
		|| uniteCourante.UL == INF || uniteCourante.UL == EGAL || uniteCourante.UL == EGALEGAL)
		consommer();
	else
		syntaxError(eComparaison);
}

void Syntaxique::identif()
{
	if (uniteCourante.UL == IDENT) {
		consommer();
	}
	else
		syntaxError(eIdentif);
}


void Syntaxique::cte()
{
	if (uniteCourante.UL == CONST) {
		consommer();
	}
	else
		syntaxError(eCte);
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

bool Syntaxique::uniteCouranteEst(string identifiant)
{
	return uniteCourante.UL == IDENT && uniteCourante.attribut == lexical->identifiants.existe(identifiant);
}

//Destructeur
Syntaxique::~Syntaxique()
{
}