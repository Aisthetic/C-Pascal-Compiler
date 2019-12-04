#include "Syntaxique.h"
#include "Lexical.h"
#include "Constants.h"
using namespace std;



//Constructeurs
Syntaxique::Syntaxique(string inputFile)
{
	lexical = new Lexical();
	lexical->setInput(inputFile);
	uniteCourante = { END,0 };
}

Syntaxique::Syntaxique(Lexical* pLexical)
{
	lexical = pLexical;
	uniteCourante = { END,0 };
}

//Functions

/// <summary>
///	 Starts checking the syntax of the current file loaded in the lexical parser
/// </summary>
void Syntaxique::startParsing()
{
	// Gestion du fichier XML
	xmlFile.open(XML_DIRECTORY + "/"+ lexical->inputFilename +".xml");
	uniteCourante = lexical->uniteSuivante();
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
	else if (uniteCourante.UL== MAIN) // TODO: mettre une production pour le main seul ?
	{
		xmlOpen("main");
		uniteCourante = lexical->uniteSuivante();
		consommer("parOuv");
		listeDeParametres();
		consommer("parFerm");
		listeDeDeclarations();
		consommer("accOuv");
		listeInstructions();
		consommer("accFerm");
		xmlClose("main");
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
		consommer("Ident");
		consommer("parOuv");
		listeDeParametres();
		consommer("parFerm");
		listeDeDeclarations();
		consommer("accOuv");
		listeInstructions();
		consommer("accFerm");
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
	if (estPremierDe(eDeclarations))
	{
		declarations();
	}
	else if (estSuivantDe(eListeDeDeclarations))
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
	if (estPremierDe(eDeclarations))
	{
		declaration();
		declarationsPrime();
	}
	else {
		syntaxError(eDeclaration);
	}
	xmlClose("declarations");
}

void Syntaxique::declarationsPrime()
{
	xmlOpen("declarationsPrime");
	if(estPremierDe(eDeclarationsPrime))
	{
		consommer("virg");
		declaration();
		declarationsPrime();
	}
	else if(estSuivantDe(eDeclarationsPrime)){
		//silence is golden
	}
	else {
		syntaxError(eDeclarationsPrime);
	}
	xmlClose("declarationsPrime");
}

void Syntaxique::declaration()
{
	xmlOpen("declaration");
	if (uniteCourante.UL == ENTIER)
	{
		consommer("Entier");
		declarationPrime();
	}
	else if (uniteCourante.UL == CAR)
	{
		consommer("Car");
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
		consommer("ENTIER");
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
	if (estPremierDe(eDeclarationSeconde))
	{
		consommer("CROVR");
		expression();
		consommer("OCROFER");
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
	else if (estSuivantDe(eParametresPrime))
	{
		//silence is golden
	}
	else { syntaxError(eParametresPrime); }
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
		consommer("PointVirg");
		listeInstructions();
	}
	else if (estSuivantDe(eListeInstructions))
	{
		//silence is golden
	}
	else { syntaxError(eListeInstructions); }
	xmlClose("listeInstructions");
}

void Syntaxique::instruction() //URFENT TODO: REMOVE IS MOT CLE
{
	xmlOpen("instruction");
	if (estPremierDe(eIdentificateur)) {
		identif();
		instructionPrime();
	}
	else if (estPremierDe(eInstruction)) {
		if (isMotCle("retour")) {
			consommer("retour");
			expression();
		}
		else if (uniteCourante.UL == SI) {
			consommer("si");
			expression();
			if (isMotCle("alors")) {
				consommer("alors");
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
				consommer("faire");
				consommer("{");
				listeInstructions();
				consommer("}");
			}
			else { return syntaxError(eInstruction); }
		}
		else if (isMotCle("ecrire")) {
			consommer("ecrire");
			consommer("(");
			expression();
			consommer(")");
		}
		else { return syntaxError(eInstruction); }
	}
	xmlClose("instruction");//retard dair open hna
}

void Syntaxique::instructionPrime()
{
	xmlOpen("instructionPrime");
	if (estPremierDe(eInstructionTriple)) {
		instructionTriple();
	}
	else if (eInstruction) {
		consommer("croOuv");
		expression();
		consommer("croFerm");
		consommer("egal");
		instructionTriple();
	}
	else { syntaxError(eInstructionPrime); }
	xmlClose("instructionPrime");
}

void Syntaxique::instructionSeconde()
{
	xmlOpen("instructionSeconde");
	if (isMotCle("sinon")) {
		consommer("sinon");
		consommer("{");
		listeInstructions();
		consommer("}");
	} 
	else if (estSuivantDe(eInstructionSeconde))
	{
		//silence is golden
	}
	else { syntaxError(eInstructionSeconde); }
	xmlClose("instructionSeconde");
}
void Syntaxique::instructionTriple()
{
	xmlOpen("instructionTriple");
	if (isMotCle("lire")) {
		consommer("lire");
		consommer("(");
		consommer(")");
	}
	else if (estPremierDe(eExpression)) {
		expression();
	}
	else { syntaxError(eInstructionTriple); }
	xmlClose("instructionTriple");
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
	else if (estSuivantDe(eExpressionPrime)) {
		//silence is golden
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
        consommer("sous"); 
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
		consommer("add");
		terme();
		expressionSimplePrime();
	}
	else if(uniteCourante.UL == SOUS ) {
		consommer("sous");
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
		consommer("mul");
		facteur();
		termePrime();
	}
	else if (uniteCourante.UL == DIV ) {
		consommer("div");
		facteur();
		termePrime();
	}
	else if (estSuivantDe(eTermePrime)) {
		//doz 7yd
	}
	else {
		syntaxError(eTermePrime);
	}
	xmlClose("termePrime");
}

void Syntaxique::termePrioritaire(){
	xmlOpen("termePrioritaire");
	if (uniteCourante.UL == NON) {
		consommer("non");
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

void Syntaxique::facteur(){//URGENT TODO: Remake
	xmlOpen("facteur");
	if (estPremierDe(eIdentificateur)) {
		identif();
		facteurPrime();
	}
	else if(estPremierDe(eCte)){
		cte();
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer("parOuv");
		expression();
		if (uniteCourante.UL == PARFERM)
			consommer("parFerm");
		else
			syntaxError(eFacteur);//à revoir
	}
	else if(uniteCourante.UL == QUOTE){
        consommer("Quote"); 
		if (uniteCourante.UL == CAR) {
			consommer("car");
		}
		else syntaxError(eCaractere);
		consommer("quote");
	}
	else {
		syntaxError(eFacteur);
	}
	xmlClose("facteur");
}
	
void Syntaxique::facteurPrime(){
	xmlOpen("facteurPrime");
	if (uniteCourante.UL == CROOUV) {
		consommer("CorOuv");
		expression();
		consommer("croOuv"); 
	}
	else if (uniteCourante.UL == PAROUV ) {
		consommer("ParOuv");
		parametresEffectifs();
		consommer("parFerm"); 
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
		consommer("OpLogique");
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
		consommer("OpComp");
	else
		syntaxError(eComparaison);
	xmlClose("comparaison");
}

void Syntaxique::identif()
{
	xmlOpen("identif");
	if (uniteCourante.UL == IDENT) {
		consommer("identif");
	}
	else
		syntaxError(eIdentificateur);
	xmlClose("identif");
}

void Syntaxique::cte()
{
	xmlOpen("cte");
	if (uniteCourante.UL == CONST) {
		consommer("const");
	}
	else
		syntaxError(eCte);
	xmlClose("cte");
}

//Methods

//void Syntaxique::consommer() {//n�cessaire pour savoir ce qu'on a consomm� (exemple lorsqu'on consomme le ;)
//	uniteCourante = lexical->uniteSuivante();
//}

void Syntaxique::consommer(string expected) {
	bool expectedCorrect = false;//true si on trouve ce qu'il fallait consommé
	if (uniteCourante.UL == IDENT) {
		// TODO: handle errors correctly
		//return uniteCourante.attribut == lexical->identifiants.existe(expected); 
	}
	
	//Xml pour les terminaux
	xmlOpen(expected);
	xmlClose(expected);
	uniteCourante = lexical->uniteSuivante();
}
//checks if the caracter is premier de l'unite en param
bool Syntaxique::estPremierDe(Production production) { 
	switch (production)//TODO: eExpressionPrime
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
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR || estSuivantDe(eListeDeDeclarations);
		break;
	case eDeclarations:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eDeclarationsPrime:
		return uniteCourante.UL == VIRG || estSuivantDe(eDeclarationsPrime);
		break;
	case eDeclaration:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eDeclarationPrime:
		return uniteCourante.UL == VIRG || estSuivantDe(production);
		break;
	case eDeclarationSeconde:
		return uniteCourante.UL == CROOUV || estSuivantDe(eDeclarationSeconde);
		break;
	case eListeParametres:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR || estSuivantDe(eListeParametres);
		break;
		//outidrarine finishes

		//souhail starts
	case eExpressionLogique:
		return estPremierDe(eExpressionSimple) == true;
		break;
	case eExpressionLogiquePrime:
		return estPremierDe(eComparaison) == true || estSuivantDe(production);;
		break;
	case eExpressionSimple:
		return uniteCourante.UL == CONST || uniteCourante.UL == CONSTCAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE || uniteCourante.UL == NON || uniteCourante.UL == SOUS;
		break;	
	case eExpressionSimplePrime:
		return uniteCourante.UL == ADD || uniteCourante.UL == SOUS || estSuivantDe(production);
		break;	
	case eTerme:
		return uniteCourante.UL == CONST || uniteCourante.UL == CONSTCAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE || uniteCourante.UL == NON ;
		break;
	case eTermePrime:
		return uniteCourante.UL == MUL || uniteCourante.UL == DIV || estSuivantDe(production);
		break;
	case eTermePrioritaire:
		return estPremierDe(eTerme) == true;
		break;
	case eFacteur:
		return uniteCourante.UL == CONST || uniteCourante.UL == CONSTCAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE ;
		break;
	case eFacteurPrime:
		return uniteCourante.UL == PAROUV || uniteCourante.UL == CROOUV || estSuivantDe(production);
		break;
		//souhail finishes
	//begin zac
	case eParametresEffectifs:
		return uniteCourante.UL == MUL || uniteCourante.UL == DIV || estSuivantDe(production);
		break;
	case eExpressions: //todo
		return estPremierDe(eExpression);
		break;
	case eExpressionsPrime:
		return uniteCourante.UL == VIRG || estSuivantDe(production);;
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
	case eExpression:
		return estPremierDe(eExpressionSimple);
	case eExpressionPrime:
		return uniteCourante.UL == ET || uniteCourante.UL == OU || estSuivantDe(production);
	//end zac

	// start testoxe
	case eParametres :
		return uniteCourante.attribut == ENTIER || uniteCourante.UL == CAR || estSuivantDe(eParametres);
		break;
	case eParametresPrime :
		return uniteCourante.UL == VIRG;
		break;
	case eParametre : 
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eListeInstructions :
		return estSuivantDe(eListeInstructions) || estSuivantDe(eExpression) || estPremierDe(eExpression) || uniteCourante.UL == IDENT || uniteCourante.UL == RETOUR || uniteCourante.UL == SI || uniteCourante.UL == TANTQUE || uniteCourante.UL == MOTCLE;
		break;
	case eInstruction :
		return estPremierDe(eExpression) || uniteCourante.UL == IDENT || uniteCourante.UL == MOTCLE || uniteCourante.UL == SI || uniteCourante.UL == TANTQUE;
		break;
	case eInstructionPrime :
		return uniteCourante.UL == EGAL || uniteCourante.UL == CROOUV;
		break;
	case eInstructionSeconde :
		return uniteCourante.UL == SINON || estSuivantDe(production);
		break;
	case eInstructionTriple :
		return estPremierDe(eExpression) || uniteCourante.UL == LIRE;
		break;

	default:
		cout << "Production non reconnue" << endl;
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
		return uniteCourante.UL == VIRG || uniteCourante.UL == PTVRG;
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
	case eExpressions: 
		return uniteCourante.UL == PARFERM;
		break;
	case eExpressionsPrime:
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

	case eExpression:
		return uniteCourante.UL == VIRG || uniteCourante.UL == ALORS || uniteCourante.UL == FAIRE || uniteCourante.UL == CROFER || uniteCourante.UL == ACCFERM || uniteCourante.UL == PTVRG || uniteCourante.UL == PARFERM;
	case eExpressionPrime:
		return uniteCourante.UL == VIRG || uniteCourante.UL == ALORS || uniteCourante.UL == FAIRE || uniteCourante.UL == CROFER || uniteCourante.UL == ACCFERM || uniteCourante.UL == PTVRG || uniteCourante.UL == PARFERM;




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
	end();
}