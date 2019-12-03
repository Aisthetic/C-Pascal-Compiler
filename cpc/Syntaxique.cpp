#include "Syntaxique.h"
#include "Lexical.h"
using namespace std;

Syntaxique::Syntaxique(string inputFile)
{
	lexical = new Lexical();
	lexical->setInput(inputFile);
}

//Constructeurs
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
	xmlFile.open("./lexical.xml");
	consommer();
	programme();
	if (uniteCourante.UL != END) {
		syntaxError(eEnd);
	}
	else
		printErrors();	//affiche toutes les erreurs trouv�es
	end(); //finish him!
}

bool Syntaxique::isMotCle(string mc)
{
	if (uniteCourante.UL == MOTCLE) {
		if (uniteCourante.attribut == lexical->identifiants.existe(mc)) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

void Syntaxique::end() {
	xmlFile.flush();
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
	xmlOpen("programme");
	if (estPremierDe(eListeDeDeclarations)) {
		listeDeDeclarations();
		listeDeFonctions();
	}
	else {
		syntaxError(eProgramme);
	}
	xmlClose("programme");
}

void Syntaxique::listeDeFonctions()
{
	xmlOpen("listeDeFonctions");
	if (estPremierDe(eFonction))
	{
		fonction();
		listeDeFonctions();
	}
	else if (uniteCourante.UL== MOTCLE &&uniteCourante.attribut == lexical->identifiants.existe("main")) // à affiner
	{
		consommer();
		consommer("(");
		consommer(")");
		consommer("{");
		listeInstructions();
		consommer("}");
	}
	else
	{
		syntaxError(eFonction);
	}
	xmlClose("listeDeFonctions");
}
void Syntaxique::fonction()
{
	xmlOpen("fonction");
	if (estPremierDe(eIdentificateur))
	{
		consommer();
		consommer("(");
		listeDeParametres();
		consommer(")");
		listeDeDeclarations();
		consommer("{");
		listeInstructions();
		consommer("}");
	}
	else
	{
		syntaxError(eIdentificateur);
	}
	xmlClose("fonction");
}

void Syntaxique::listeDeDeclarations()
{
	xmlOpen("listeDeDeclarations");
	if (estPremierDe(eDeclaration))
	{
		declarations();
	}
	else if (estPremierDe(eListeDeFonctions))
	{
		//silence is golden
	}
	else
	{
		syntaxError(eDeclaration);
	}
	xmlClose("listeDeDeclarations");
}

void Syntaxique::declarations()
{
	xmlOpen("declarations");
	if (estPremierDe(eDeclaration))
	{
		declaration();
		declarationPrime();
	}
	else {
		syntaxError(eDeclaration);
	}
	xmlClose("declarations");
}

void Syntaxique::declarationsPrime()
{
	xmlOpen("declarationsPrime");
	if(estPremierDe(eDeclaration))
	{
		consommer(",");
		declaration();
		declarationsPrime();
	}
	else if(estSuivantDe(eDeclarationsPrime)){
		//silence is golden
	}
	else {
		syntaxError(eListeDeDeclarationsPrime);
	}
	xmlClose("declarationsPrime");
}

void Syntaxique::declaration()
{
	xmlOpen("declaration");
	if (uniteCourante.UL == MOTCLE && uniteCourante.attribut == lexical->identifiants.existe("entier"))
	{
		consommer();
		declarationPrime();
	}
	else if (uniteCourante.UL == MOTCLE && uniteCourante.attribut == lexical->identifiants.existe("car"))
	{
		consommer();
		declarationPrime();
	}
	else
	{
		syntaxError(eDeclaration);
	}
	xmlClose("declaration");
}

void Syntaxique::declarationPrime()
{
	xmlOpen("declarationPrime");
	if (estPremierDe(eIdentificateur))
	{
		consommer();
		declarationSeconde();
	}
	else {
		syntaxError(eDeclaration);
	}
	xmlClose("declarationPrime");
}

void Syntaxique::declarationSeconde()
{
	xmlOpen("declarationSeconde");
	if (estPremierDe(eExpression))
	{
		consommer("[");
		expression();
		consommer("]");
	}
	else if (estSuivantDe(eDeclarationSeconde))
	{
		//silence is golden
	}
	else
	{
		syntaxError(eDeclarationSeconde);
	}
	xmlClose("declarationSeconde");
}

void Syntaxique::listeDeParametres()
{
	xmlOpen("listeDeParametres");
	if (estPremierDe(eParametre))
	{
		parametre();
	}
	else if (estSuivantDe(eListeParametres))
	{
		//silence is golden
	}
	else
	{
		syntaxError(eListeParametres);
	}
	xmlClose("listeDeParametres");
}

void Syntaxique::parametres()
{
	xmlOpen("parametres");
	if (estPremierDe(eParametre)) {
		parametre();
		parametresPrime();
	}
	else { syntaxError(eParametres); }
	xmlClose("parametres");
}

void Syntaxique::parametresPrime()
{
	xmlOpen("parametresPrime");
	if (estPremierDe(eParametresPrime)) {
		consommer(",");
		parametre();
		parametresPrime();
	}
	else { syntaxError(eParametresPrime); }
	// ajouter traitement epsilon
	xmlClose("parametresPrime");
}

void Syntaxique::parametre()
{
	xmlOpen("parametre");
	if (isMotCle("entier")) {
		identif();
	}
	else if (isMotCle("Car")) {
		identif();
	}
	else { syntaxError(eParametre); }
	xmlClose("parametre");
}

void Syntaxique::listeInstructions()
{
	xmlOpen("listeInstructions");
	if (estPremierDe(eInstruction)) {
		instruction();
		consommer(";");
		listeInstructions();
	}
	else { syntaxError(eListeInstructions); }
	// traitement epsilon
	xmlClose("listeInstructions");
}

void Syntaxique::instruction() // a revoir
{
	xmlOpen("instruction");
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
			consommer("(");
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
	xmlOpen("instruction");
}

void Syntaxique::instructionPrime()
{
	xmlOpen("instructionPrime");
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
	xmlClose("instructionPrime");
}

void Syntaxique::instructionTriple()
{
	xmlOpen("instructionTriple");
	if (isMotCle("lire")) {
		consommer();
		consommer("(");
		consommer(")");
	}
	else if (estPremierDe(eExpression)) {
		expression();
	}
	else { syntaxError(eInstructionTriple); }
	xmlClose("instructionTriple");
}

void Syntaxique::instructionSeconde()
{
	xmlOpen("instructionSeconde");
	if (isMotCle("sinon")) {
		consommer();
		consommer("{");
		listeInstructions();
		consommer("}");
	} 
	// traitement epsilon
	else { syntaxError(eInstructionSeconde); }
	xmlClose("instructionSeconde");
}

void Syntaxique::expression()
{
	xmlOpen("expression");
	if (estPremierDe(eExpressionLogique)) {
		expressionLogique();
		expressionPrime();
	} 
	else { syntaxError(eExpression); }
	xmlClose("expression");
}

void Syntaxique::expressionPrime()
{
	xmlOpen("expressionPrime");
	if (estPremierDe(eOperateurLogique)) {
		operateurLogique();
		expressionLogique();
		expressionPrime();
	}

	else { syntaxError(eExpressionPrime); }
	xmlClose("expressionPrime");
}

void Syntaxique::expressionLogique(){
	xmlOpen("expressionLogique");
	if (estPremierDe(eExpressionSimple)) {
		expressionSimple();
		expressionLogiquePrime();
	}
	else {
		syntaxError(eExpressionLogique);
	}
	xmlClose("expressionLogique");
}

void Syntaxique::expressionLogiquePrime(){
	xmlOpen("expressionLogiquePrime");
	if (estPremierDe(eComparaison)) {
		comparaison();
		expressionSimple();
		expressionLogiquePrime();
	}
	else if (estSuivantDe(eExpressionLogiquePrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eExpressionLogiquePrime);
	}
	xmlClose("expressionLogiquePrime");
}

void Syntaxique::expressionSimple(){
	xmlOpen("expressionSimple");
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
	xmlClose("expressionSimple");
}

void Syntaxique::expressionSimplePrime(){
	xmlOpen("expressionSimplePrime");
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
	else if (estSuivantDe(eExpressionSimplePrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eExpressionSimplePrime);
	}
	xmlClose("expressionSimplePrime");
}

void Syntaxique::terme(){
	xmlOpen("terme");
	if (estPremierDe(eTermePrioritaire)) {
		termePrioritaire();
		termePrime();
	}
	else {
		syntaxError(eTerme);
	}
	xmlClose("terme");
}
void Syntaxique::termePrime(){
	xmlOpen("termePrime");
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
	else if (estSuivantDe(eTermePrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eTermePrime);
	}
	xmlOpen("termePrime");
}

void Syntaxique::termePrioritaire(){
	xmlOpen("termePrioritaire");
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
	xmlClose("termePrioritaire");
}

void Syntaxique::facteur(){
	xmlOpen("facteur");
	if (estPremierDe(eIdentificateur)) {
		identif();
		facteurPrime();
	}
	else if(estPremierDe(eCte)){
		cte();
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer();
		expression();
		if (uniteCourante.UL == PARFERM)
			consommer();
		else
			syntaxError(eFacteur);//à revoir
	}
	else if(uniteCourante.UL == QUOTE){
        consommer(); 
		if (uniteCourante.UL == CAR) {
			consommer();
			}
			else syntaxError(eCaractere);
		
		consommer("\'");
	}
	else {
		syntaxError(eFacteur);
	}
	xmlClose("facteur");
}
	
void Syntaxique::facteurPrime(){
	xmlOpen("facteurPrime");
	if (uniteCourante.UL == CROOUV) {
		consommer();
		expression();
		consommer("]"); 
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer();
		parametresEffectifs();
		consommer(")"); 
	}
	else if (estSuivantDe(eFacteurPrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eFacteurPrime);
	}
	xmlClose("facteurPrime");
}

void Syntaxique::parametresEffectifs(){
	xmlOpen("parametresEffectifs");
	if (estPremierDe(eExpressions)) {
		expressions(); 
	}
	else if (estSuivantDe(eParametresEffectifs)) {
		//doz 7yd
	}
	else {
		syntaxError(eParametresEffectifs);
	}
	xmlClose("parametresEffectifs");
}

void Syntaxique::expressions()
{
	xmlOpen("expressions");
	if(estPremierDe(eExpression)){
		expression();
		expressionPrime();
	}
	else {
		syntaxError(eExpression);
	}
	xmlClose("expressions");
}

void Syntaxique::expressionsPrime()
{
	xmlOpen("expressionsPrime");
	if (uniteCourante.UL == VIRG) {
		expression();
		expressionPrime();
	}
	else if (estSuivantDe(eExpressionsPrime)) {
		//doz 7yd
	}
	else { 
		syntaxError(eExpressionsPrime); 
	}
	xmlClose("expressionsPrime");
}

void Syntaxique::operateurLogique()
{
	xmlOpen("operateurLogique");
	if (uniteCourante.UL == OU || uniteCourante.UL == ET) {
		consommer();
	}
	else {
		syntaxError(eOperateurLogique);
	}
	xmlClose("operateurLogique");
}

void Syntaxique::comparaison()
{
	xmlOpen("comparaison");
	if (uniteCourante.UL == SUP || uniteCourante.UL == INFEGAL || uniteCourante.UL == SUPEGAL
		|| uniteCourante.UL == INF || uniteCourante.UL == EGAL || uniteCourante.UL == EGALEGAL)
		consommer();
	else
		syntaxError(eComparaison);
	xmlClose("comparaison");
}

void Syntaxique::identif()
{
	xmlOpen("identif");
	if (uniteCourante.UL == IDENT) {
		consommer();
	}
	else
		syntaxError(eIdentificateur);
	xmlClose("identif");
}

void Syntaxique::cte()
{
	xmlOpen("cte");
	if (uniteCourante.UL == CONST) {
		consommer();
	}
	else
		syntaxError(eCte);
	xmlClose("cte");
}

//Methods

void Syntaxique::consommer() {//n�cessaire pour savoir ce qu'on a consomm� (exemple lorsqu'on consomme le ;)
	uniteCourante = lexical->uniteSuivante();
}

void Syntaxique::consommer(string expected) {
	bool expectedCorrect = false;//true si on trouve ce qu'il fallait consommé
	if (uniteCourante.UL == IDENT) {
		// TODO: handle errors correctly
		//return uniteCourante.attribut == lexical->identifiants.existe(expected); 
	}
	uniteCourante = lexical->uniteSuivante();
}
//checks if the caracter is premier de l'unite en param
bool Syntaxique::estPremierDe(Production production) { 
	switch (production)
	{
		//outidrarine starts
	case eProgramme:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eListeDeFonctions:
		return uniteCourante.UL == IDENT || uniteCourante.UL == MAIN;
		break;
	case eFonction:
		return uniteCourante.UL == IDENT;
		break;
	case eListeDeDeclarations:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eDeclarations:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eDeclarationsPrime:
		return uniteCourante.UL == VIRG;
		break;
	case eDeclaration:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eDeclarationPrime:
		return uniteCourante.UL == VIRG;
		break;
	case eDeclarationSeconde:
		return uniteCourante.UL == ACCOUV;
		break;
	case eListeParametres:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
		//outidrarine finishes

		//souhail starts
	case eExpressionLogique:
		return estPremierDe(eExpressionSimple) == true;
		break;
	case eExpressionLogiquePrime:
		return estPremierDe(eComparaison) == true;
		break;
	case eExpressionSimple:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE || uniteCourante.UL == NON || uniteCourante.UL == SOUS;
		break;	
	case eExpressionSimplePrime:
		return uniteCourante.UL == ADD || uniteCourante.UL == SOUS;
		break;	
	case eTerme:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE || uniteCourante.UL == NON ;
		break;
	case eTermePrime:
		return uniteCourante.UL == MUL || uniteCourante.UL == DIV;
		break;
	case eTermePrioritaire:
		return estPremierDe(eTerme) == true;
		break;
	case eFacteur:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE ;
		break;
	case eFacteurPrime:
		return uniteCourante.UL == PAROUV || uniteCourante.UL == CROOUV;
		break;
		//souhail finishes
	//begin zac
	case eParametresEffectifs:
		return uniteCourante.UL == MUL || uniteCourante.UL == DIV;
		break;
	case eExpression: //todo
		break;
	case eExpressionPrime:
		return uniteCourante.UL == VIRG;
		break;
	case eOperateurLogique:
		return uniteCourante.UL == OU || uniteCourante.UL == ET;
	case eComparaison:
		return uniteCourante.UL == INF || uniteCourante.UL == SUP || uniteCourante.UL == INFEGAL
			|| uniteCourante.UL == EGALEGAL;
	case eIdentificateur:
		return uniteCourante.UL == IDENT;
	case eCte:
		return uniteCourante.UL == CONST;
	//end zac

	// start testoxe
	case eParametres :
		return uniteCourante.attribut == ENTIER || uniteCourante.UL == CAR;
		break;
	case eParametresPrime :
		return uniteCourante.UL == VIRG;
		break;
	case eParametre : 
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eListeInstructions :
		return estPremierDe(eExpression) || uniteCourante.UL == IDENT || uniteCourante.UL == RETOUR || uniteCourante.UL == SI || uniteCourante.UL == TANTQUE || uniteCourante.UL == MOTCLE;
		break;
	case eInstruction :
		return estPremierDe(eExpression) || uniteCourante.UL == IDENT || uniteCourante.UL == MOTCLE || uniteCourante.UL == SI || uniteCourante.UL == TANTQUE;
		break;
	case eInstructionPrime :
		return uniteCourante.UL == EGAL || uniteCourante.UL == CROOUV;
		break;
	case eInstructionSeconde :
		return uniteCourante.UL == SINON;
		break;
	case eInstructionTriple :
		return estPremierDe(eExpression) || uniteCourante.UL == LIRE;
		break;

	default:
		throw new exception("Production non reconnue");
		break;
	}
}

bool Syntaxique::estSuivantDe(Production production) {
	switch (production)
	{
		//outidrarine starts
	case eProgramme:
		return uniteCourante.UL == END;
		break;
	case eListeDeFonctions:
		return uniteCourante.UL == END;
		break;
	case eFonction:
		return uniteCourante.UL == IDENT || uniteCourante.UL == MAIN ;
		break;
	case eListeDeDeclarations:
		return uniteCourante.UL == IDENT || uniteCourante.UL == MAIN;
		break;
	case eDeclarations:
		return uniteCourante.UL == PTVRG;
		break;
	case eDeclarationsPrime:
		return uniteCourante.UL == VIRG || uniteCourante.UL == PTVRG;
		break;
	case eDeclaration:
		return uniteCourante.UL == VIRG || uniteCourante.UL == PTVRG;
		break;
	case eDeclarationPrime:
		return uniteCourante.UL == VIRG || uniteCourante.UL == PTVRG;
		break;
	case eDeclarationSeconde:
		return uniteCourante.UL == PAROUV;
		break;
	case eListeParametres:
		return uniteCourante.UL == PAROUV;
		break;
		//outidrarine finishes
	
		//souhail starts
	case eExpressionLogique:
		return estSuivantDe(eExpression) == true || uniteCourante.UL == ET || uniteCourante.UL == OU ;
		break;
	case eExpressionLogiquePrime:
		return estSuivantDe(eExpressionLogique) == true;
		break;
	case eExpressionSimple:
		return estSuivantDe(eExpressionLogique) == true || estPremierDe(eComparaison) == true;
		break;
	case eExpressionSimplePrime:
		return estSuivantDe(eExpressionSimple) == true;
		break;	
	case eTerme:
		return estSuivantDe(eExpressionSimple) == true || uniteCourante.UL == ADD || uniteCourante.UL == SOUS;
		break;
	case eTermePrime:
		return estSuivantDe(eTerme) == true;
		break;
	case eTermePrioritaire:
		return estSuivantDe(eTerme) == true ||  uniteCourante.UL == MUL || uniteCourante.UL == DIV;
		break;
	case eFacteur:
		return estSuivantDe(eTermePrioritaire) == true;
		break;
	case eFacteurPrime:
		return estSuivantDe(eTermePrioritaire) == true;
		break;
	case eParametresEffectifs:
		return uniteCourante.UL == PARFERM;
		break;
		//souhail finishes
	//begin zac
	case eExpression: 
		return uniteCourante.UL == PARFERM;
		break;
	case eExpressionPrime:
		return uniteCourante.UL == PARFERM;
		break;
	case eOperateurLogique:
		return estPremierDe(eExpressionLogique);
	case eComparaison:
		return uniteCourante.UL == IDENT || uniteCourante.UL == CONST || uniteCourante.UL == CAR
			|| uniteCourante.UL == PAROUV || uniteCourante.UL == NON || uniteCourante.UL == SOUS;
	case eIdentificateur:
		return estPremierDe(eFacteur) || estSuivantDe(eFacteur) || estPremierDe(eInstructionPrime)
			|| estSuivantDe(eParametre) || estSuivantDe(eDeclarationSeconde) || uniteCourante.UL == PAROUV ;
	case eCte:
		return estSuivantDe(eFacteur);
		//end zac

		//start testoxe
	case eParametres :
		return uniteCourante.UL == PARFERM;
		break;
	case eParametresPrime :
		return uniteCourante.UL == PARFERM;
		break;
	case eParametre :
		return uniteCourante.UL == VIRG || uniteCourante.UL == PARFERM;
		break;
	case eListeInstructions :
		return uniteCourante.UL == ACCFERM;
		break;
	case eInstruction :
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionPrime :
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionSeconde :
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionTriple :
		return uniteCourante.UL == PTVRG;
		break;

	default:
		throw new exception("Production non reconnue");
		break;
	}
}



void Syntaxique::syntaxError(Production prod) {

}

//Destructeur
Syntaxique::~Syntaxique()
{
}