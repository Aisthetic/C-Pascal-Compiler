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

bool Syntaxique::isMotCle(string mc)
{
	if (uniteCourante.UL == MOTCLE) {
		if (uniteCourante.UL == lexical->identifiants.existe(mc)) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
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
		consommer("{");
		listeInscructions();
		consommer("}");
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
		consommer("(");
		listeDeParametres();
		consommer(")");
		listeDeDeclarations();
		consommer("{");
		listeInscructions();
		consommer("}");
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
		consommer(",");
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
	if (estPremierDe(eParametre)) {
		parametre();
		parametresPrime();
	}
	else { syntaxError(eParametres); }
}

void Syntaxique::parametresPrime()
{
	if (estPremierDe(eParametresPrime)) {
		consommer(",");
		parametre();
		parametresPrime();
	}
	else { syntaxError(eParametresPrime); }
	// ajouter traitement epsilon
}

void Syntaxique::parametre()
{
	if (isMotCle("entier")) {
		identif();
	}
	else if (isMotCle("Car")) {
		identif();
	}
	else { syntaxError(eParametre); }
}

void Syntaxique::listeInstructions()
{
	if (estPremierDe(eInstruction)) {
		instruction();
		consommer(";");
		listeInstructions();
	}
	else { syntaxError(eListeInstructions); }
	// traitement epsilon
}

void Syntaxique::instruction() // a revoir
{
	if (estPremierDe(eIdentificateur)) {
		identif();
		instructionPrime();
	}
	else if (estPremierDe(eInstruction)) {
		if (isMotCle("retour")) {
			consommer();
			expression();
		}
		else if (isMotCle("si")) {
			consommer();
			expression();
			if (isMotCle("alors")) {
				consommer();
				consommer("{");
				listeInstructions();
				consommer("}");
				instructionSeconde();
			}
			else { return syntaxError(eInstruction); }
		}
		else if (isMotCle("tantque")) {
<<<<<<< HEAD
			consommer();
			consommer('(');
=======
			consommer("(");
>>>>>>> 2dc456ca00fc85b2bdf56aec08f3334529de640d
			expression();
			consommer(")");
			if (isMotCle("faire")) {
				consommer();
				consommer("{");
				listeInstructions();
				consommer("}");
			}
			else { return syntaxError(eInstruction); }
		}
		else if (isMotCle("ecrire")) {
			consommer();
			consommer("(");
			expression();
			consommer(")");
		}
		else { return syntaxError(eInstruction); }
	}
}

void Syntaxique::instructionPrime()
{
	if (estPremierDe(eInstructionTriple)) {
		instructionTriple();
	}
	else if (eInstruction) {
		consommer("[");
		expression();
		consommer("]");
		consommer("=");
		instructionTriple();
	}
	else { syntaxError(eInstructionPrime); }
}

void Syntaxique::instructionTriple()
{
	if (isMotCle("lire")) {
		consommer();
		consommer("(");
		consommer(")");
	}
	else if (estPremierDe(eExpression)) {
		expression();
	}
	else { syntaxError(eInstructionTriple); }
}

void Syntaxique::instructionSeconde()
{
	if (isMotCle("sinon")) {
		consommer();
		consommer("{");
		listeInstructions();
		consommer("}");
	} 
	// traitement epsilon
	else { syntaxError(eInstructionSeconde); }
}

void Syntaxique::expression()
{
	if (estPremierDe(eExpressionLogique)) {
		expressionLogique();
		expressionPrime();
	} 
	else { syntaxError(eExpression); }
}

void Syntaxique::expressionPrime()
{
	if (estPremierDe(eOperateurLogique)) {
		operateurLogique();
		expressionPrime();
	}
	else { syntaxError(eExpressionPrime); }
}

void Syntaxique::expressionLogique(){
	if (estPremierDe(eExpressionSimple)) {
		expressionSimple();
		expressionLogiquePrime();
	}
	else {
		syntaxError(eExpressionLogique);
	}
}

void Syntaxique::expressionLogiquePrime(){
	if (estPremierDe(eComparaison)) {
		comparaison();
		expressionSimple();
		expressionLogiquePrime();
	}
}

void Syntaxique::expressionSimple(){
	if (estPremierDe(eTerme)) {
		terme();
		expressionSimplePrime();
	}
	else if(uniteCourante.UL == SOUS ){
        consommer(); 
		terme();
		expressionSimplePrime();
	}
	else {
		syntaxError(eExpression);
	}
}

void Syntaxique::expressionSimplePrime(){
	if (uniteCourante.UL == ADD) {
		consommer();
		terme();
		expressionSimplePrime();
	}
	else if(uniteCourante.UL == SOUS ) {
		consommer();
		terme();
		expressionSimplePrime();
	}
}

void Syntaxique::terme(){
	if (estPremierDe(eTermePrioritaire)) {
		termePrioritaire();
		termePrime();
	}
	else {
		syntaxError(eTerme);
	}
}
void Syntaxique::termePrime(){
	if (uniteCourante.UL == MUL) {
		consommer();
		facteur();
		termePrime();
	}
	else if (uniteCourante.UL == DIV ) {
		consommer();
		facteur();
		termePrime();
	}
}

void Syntaxique::termePrioritaire(){
	if (uniteCourante.UL == NON) {
		consommer();
		facteur();
	}
	else if (estPremierDe(eFacteur) ) {
		facteur();
	}
	else {
		syntaxError(eTermePrioritaire);
	}
}

void Syntaxique::facteur(){
	if (estPremierDe(eIdentif)) {
		identif();
		facteurPrime();
	}
	else if(estPremierDe(eCte)){
		cte();
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer();
		expression();
<<<<<<< HEAD
	    consommer(')');
=======
		if (uniteCourante.UL == PARFERM)
			consommer();
		else
			syntaxError(eFacteur);//à revoir
>>>>>>> 2dc456ca00fc85b2bdf56aec08f3334529de640d
	}
	else if(uniteCourante.UL == CAR){
        consommer(); 
<<<<<<< HEAD
		lettre();
		consommer('\'');
=======
>>>>>>> 2dc456ca00fc85b2bdf56aec08f3334529de640d
	}
	else {
		syntaxError(eFacteur);
	}
}
	
void Syntaxique::facteurPrime(){
	if (uniteCourante.UL == CROOUV) {
		consommer();
		expression();
		consommer(']'); 
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer();
		parametresEffictifs();
		consommer(')'); 
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
	else { // souhail : source d'erreur	
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

//Methods

<<<<<<< HEAD
void Syntaxique::consommer(char str = ' ') { //n�cessaire pour savoir ce qu'on a consomm� (exemple lorsqu'on consomme le ;)
	uniteCourante = lexical->uniteSuivante(); 
	// souhail : ajouter le traitement de verification du suivant
=======
void Syntaxique::consommer() {//n�cessaire pour savoir ce qu'on a consomm� (exemple lorsqu'on consomme le ;)
	uniteCourante = lexical->uniteSuivante();
>>>>>>> 2dc456ca00fc85b2bdf56aec08f3334529de640d
}

void Syntaxique::consommer(string expected) {
	bool expectedCorrect = false;//true si on trouve ce qu'il fallait consommé
	if (uniteCourante.UL == IDENT) {
		return uniteCourante.attribut == lexical->identifiants.existe(expected);
	}
	uniteCourante = lexical->uniteSuivante();
}
//checks if the caracter is premier de l'unite en param
bool Syntaxique::estPremierDe(Production unite) { 
	return false;
}

bool Syntaxique::estSuivantDe(Production unite) {
	return false;
}



void Syntaxique::syntaxError(Production prod) {

}

//Destructeur
Syntaxique::~Syntaxique()
{
}