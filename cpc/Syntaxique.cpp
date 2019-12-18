#include "Syntaxique.h"
#include "Lexical.h"
#include "Constants.h"
#include "ConsoleHandler.h"
#include <algorithm>
using namespace std;



//Constructeurs
Syntaxique::Syntaxique(string inputFile, bool logTableIden, bool logMotsRes)
{
	lexical = new Lexical();
	lexical->setInput(inputFile, logTableIden, logMotsRes);
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
	xmlFile.open(XML_DIRECTORY + "/" + lexical->getInputFileNameWithoutExt() + ".xml");
	if (!xmlFile.is_open())
		logError("Couldn't open xml file, check if xml dir is already created.");
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
	//Logging the errors : We're trying to be precise and avoid printing too much errors
	//First, we check if there's multiple errors targeting the same Ln&Col
	for (auto const& element : syntaxErrors) {
		/*auto line = element.second.first;
		auto col = element.second.second;*/
	}
	//Writing XML file
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
	if (estPremierDe(eListeDeFonctions) && uniteCourante.UL != MAIN)
	{
		fonction();
		listeDeFonctions();
	}
	else if (uniteCourante.UL == MAIN) // TODO: mettre une production pour le main seul ?
	{
		xmlOpen("main");
		uniteCourante = lexical->uniteSuivante();
		consommer(PAROUV);
		listeDeParametres();
		consommer(PARFERM);
		listeDeDeclarations();
		consommer(ACCOUV);
		listeInstructions();
		consommer(ACCFERM);
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
		consommer(IDENT);
		consommer(PAROUV);
		listeDeParametres();
		consommer(PARFERM);
		listeDeDeclarations();
		consommer(ACCOUV);
		listeInstructions();
		consommer(ACCFERM);
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
	if (estPremierDe(eListeDeDeclarations))
	{
		declarations();
		consommer(PTVRG);
	}
	else if (estSuivantDe(eListeDeDeclarations))
	{
		//silence is golden
	}
	else
	{
		syntaxError(eListeDeDeclarations);
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
	if (estPremierDe(eDeclarationsPrime))
	{
		consommer(VIRG);
		declaration();
		declarationsPrime();
	}
	else if (estSuivantDe(eDeclarationsPrime)) {
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
		consommer(ENTIER);
		declarationPrime();
	}
	else if (uniteCourante.UL == CAR)
	{
		consommer(CAR);
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
		consommer(IDENT);
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
		consommer(CROOUV);
		expression();
		consommer(CROFER);
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
		parametres();
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
		consommer(VIRG);
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
	if (uniteCourante.UL==CAR) {
		consommer(CAR);
		identif();
	}
	else if(uniteCourante.UL == ENTIER)
	{
		consommer(ENTIER);
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
		listeInstructions();
	}
	else if (estSuivantDe(eListeInstructions))
	{
		//silence is golden
	}
	else { 
		syntaxError(eListeInstructions);
	}
	xmlClose("listeInstructions");
}

void Syntaxique::instruction() //URFENT TODO: REMOVE IS MOT CLE
{
	xmlOpen("instruction");
	if (estPremierDe(eIdentificateur)) {
		identif();
		instructionPrime();
		consommer(PTVRG);
	}
	else if (uniteCourante.UL == RETOUR)
	{
		consommer(RETOUR);
		expression();
		consommer(PTVRG);
	}
	else if (uniteCourante.UL == SI)
	{
		consommer(SI);
		expression();
		if (uniteCourante.UL == ALORS) {
			consommer(ALORS);
			consommer(ACCOUV);
			listeInstructions();
			consommer(ACCFERM);
			instructionSeconde();
		}
		else { return syntaxError(eInstruction); }
	}
	else if (uniteCourante.UL == TANTQUE)
	{
		consommer(TANTQUE);
		consommer(PAROUV);
		expression();
		consommer(PARFERM);
		if (uniteCourante.UL == FAIRE) {
			consommer(FAIRE);
			consommer(ACCOUV);
			listeInstructions();
			consommer(ACCFERM);
		}
		else { return syntaxError(eInstruction); }
	}
	else if (uniteCourante.UL == ECRIRE) {
		consommer(ECRIRE);
		consommer(PAROUV);
		expression();
		consommer(PARFERM);
		consommer(PTVRG);
	}
	else { return syntaxError(eInstruction); }

	xmlClose("instruction");//retard dair open hna
}

void Syntaxique::instructionPrime()
{
	xmlOpen("instructionPrime");
	if (estPremierDe(eInstructionPrime)) {
		consommer(EGAL);
		instructionTriple();
	}
	else if (uniteCourante.UL == CROFER) {
		consommer(CROOUV);
		expression();
		consommer(CROFER);
		consommer(EGAL);
		instructionTriple();
	}
	else { syntaxError(eInstructionPrime); }
	xmlClose("instructionPrime");
}

void Syntaxique::instructionSeconde()
{
	xmlOpen("instructionSeconde");
	if (uniteCourante.UL == SINON) {
		consommer(SINON);
		consommer(ACCOUV);
		listeInstructions();
		consommer(ACCFERM);
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
	if (uniteCourante.UL == LIRE) {
		consommer(LIRE;
		consommer(PAROUV);
		consommer(PARFERM);
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

void Syntaxique::expressionLogique() {
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

void Syntaxique::expressionLogiquePrime() {
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

void Syntaxique::expressionSimple() {
	xmlOpen("expressionSimple");
	if (estPremierDe(eTerme)) {
		terme();
		expressionSimplePrime();
	}
	else if (uniteCourante.UL == SOUS) {
		consommer("sous");
		terme();
		expressionSimplePrime();
	}
	else {
		syntaxError(eExpression);
	}
	xmlClose("expressionSimple");
}

void Syntaxique::expressionSimplePrime() {
	xmlOpen("expressionSimplePrime");
	if (uniteCourante.UL == ADD) {
		consommer("add");
		terme();
		expressionSimplePrime();
	}
	else if (uniteCourante.UL == SOUS) {
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

void Syntaxique::terme() {
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
void Syntaxique::termePrime() {
	xmlOpen("termePrime");
	if (uniteCourante.UL == MUL) {
		consommer("mul");
		facteur();
		termePrime();
	}
	else if (uniteCourante.UL == DIV) {
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

void Syntaxique::termePrioritaire() {
	xmlOpen("termePrioritaire");
	if (uniteCourante.UL == NON) {
		consommer("non");
		facteur();
	}
	else if (estPremierDe(eFacteur)) {
		facteur();
	}
	else {
		syntaxError(eTermePrioritaire);
	}
	xmlClose("termePrioritaire");
}

void Syntaxique::facteur() {//URGENT TODO: Remake
	xmlOpen("facteur");
	if (estPremierDe(eIdentificateur)) {
		identif();
		facteurPrime();
	}
	else if (estPremierDe(eCte)) {
		cte();
	}
	else if (uniteCourante.UL == PAROUV) {
		consommer("parOuv");
		expression();
		if (uniteCourante.UL == PARFERM)
			consommer("parFerm");
		else
			syntaxError(eFacteur);//à revoir
	}
	else if (uniteCourante.UL == QUOTE) {
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

void Syntaxique::facteurPrime() {
	xmlOpen("facteurPrime");
	if (uniteCourante.UL == CROOUV) {
		consommer("CorOuv");
		expression();
		consommer("croOuv");
	}
	else if (uniteCourante.UL == PAROUV) {
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

void Syntaxique::parametresEffectifs() {
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
	if (estPremierDe(eExpression)) {
		expression();
		expressionsPrime();
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
		consommer("VIRG");
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
	vector<string> expectedSymbols;
	//Gestion des erreurs
	if (expected == "parouv" || expected == "ParOuv") {
		if (uniteCourante.UL != PAROUV)
			expectedSymbols.push_back(" ')' ");
	}
	else if (expected == "const") {
		if (uniteCourante.UL != CONST)
			expectedSymbols.push_back( " const ");
	}
	else if (expected == "identif") {
		if (uniteCourante.UL != IDENT)
			expectedSymbols.push_back( " ident ");
	}
	else if (expected == "OpComp") {
		if (uniteCourante.UL != SUP && uniteCourante.UL != INF && uniteCourante.UL != EGALEGAL && uniteCourante.UL != SUPEGAL && uniteCourante.UL != INFEGAL )
			expectedSymbols.push_back( " comparaison operator ");
	}
	else if (expected == "OpLogique") {
		if (uniteCourante.UL != OU && uniteCourante.UL != ET)
			expectedSymbols.push_back( " logical operator ");
	}
	else if (expected == "VIRG") {
		if (uniteCourante.UL != VIRG)
			expectedSymbols.push_back( " ',' ");
	}
	else if (expected == "parferm") {
		if (uniteCourante.UL != PARFERM)
			expectedSymbols.push_back( " ')' ");
	}
	else if (expected == "parFerm") {
		if (uniteCourante.UL != PARFERM)
			expectedSymbols.push_back( " const ");
	}
	else if (expected == "croOuv") {
		if (uniteCourante.UL != CROOUV)
			expectedSymbols.push_back( " '[' ");
	}
	else if (expected == "quote") {
		if (uniteCourante.UL != QUOTE)
			expectedSymbols.push_back( " quote ");
	}
	else if (expected == "car") {
		if (uniteCourante.UL != CAR)
			expectedSymbols.push_back( " car ");
	}
	else if (expected == "Quote") {
		if (uniteCourante.UL != QUOTE)
			expectedSymbols.push_back( " quote ");
	}
	else if (expected == "non") {
		if (uniteCourante.UL != NON)
			expectedSymbols.push_back( " ! ");
	}
	else if (expected == "div") {
		if (uniteCourante.UL != DIV)
			expectedSymbols.push_back( " div ");
	}
	else if (expected == "mul") {
		if (uniteCourante.UL != MUL)
			expectedSymbols.push_back( " mul ");
	}
	else if (expected == "sous") {
		if (uniteCourante.UL != SOUS)
			expectedSymbols.push_back( " sous ");
	}
	else if (expected == "add") {
		if (uniteCourante.UL != ADD)
			expectedSymbols.push_back( " add ");
	}
	else if (expected == "lire") {
		if (uniteCourante.UL != LIRE)
			expectedSymbols.push_back( " lire ");
	}
	else if (expected == "}") {
		if (uniteCourante.UL != ACCFERM)
			expectedSymbols.push_back( " '}' ");
	}
	else if (expected == "{") {
		if (uniteCourante.UL != ACCOUV)
			expectedSymbols.push_back( " '{' ");
	}
	else if (expected == "sinon") {
		if (uniteCourante.UL != SINON)
			expectedSymbols.push_back( " sinon ");
	}
	else if (expected == "egal") {
		if (uniteCourante.UL != EGAL)
			expectedSymbols.push_back( " '=' ");
	}
	else if (expected == "croFerm") {
		if (uniteCourante.UL != CROFER)
			expectedSymbols.push_back( " ']' ");
	}
	else if (expected == "croOuv") {
		if (uniteCourante.UL != CROOUV)
			expectedSymbols.push_back( " '[' ");
	}
	else if (expected == "EGAL") {
		if (uniteCourante.UL != EGAL)
			expectedSymbols.push_back( " = ");
	}
	else if (expected == "PointVirg" || expected == "PTVIRG") {
	if (uniteCourante.UL != PTVRG)
		expectedSymbols.push_back( " ';' ");
	}
	else if (expected == "ecrire") {
	if (uniteCourante.UL != ECRIRE)
		expectedSymbols.push_back( " ecrire ");
	}
	else if (expected == "faire") {
	if (uniteCourante.UL != FAIRE)
		expectedSymbols.push_back( " faire  ");
	}
	else if (expected == "TANQUE") {
	if (uniteCourante.UL != TANTQUE)
		expectedSymbols.push_back( " tantque ");
	}
	else if (expected == "ACCFERM") {
	if (uniteCourante.UL != ACCFERM)
		expectedSymbols.push_back( " '}' ");
	}
	else if (expected == "ACCOUV" || expected == "accOuv") {
	if (uniteCourante.UL != ACCOUV)
		expectedSymbols.push_back( " '{' ");
	}
	else if (expected == "alors") {
	if (uniteCourante.UL != ALORS)
		expectedSymbols.push_back( " alors ");
	}
	else if (expected == "si") {
	if (uniteCourante.UL != SI)
		expectedSymbols.push_back( " si ");
	}
	else if (expected == "PointVirg") {
	if (uniteCourante.UL != PTVRG)
		expectedSymbols.push_back( " ';' ");
	}
	else if (expected == "retour") {
	if (uniteCourante.UL != RETOUR)
		expectedSymbols.push_back( " retour ");
	}
	else if (expected == "PointVirg") {
	if (uniteCourante.UL != PTVRG)
		expectedSymbols.push_back( " ';' ");
	} 
	else if (expected == "TYPE") {
	if (uniteCourante.UL != ENTIER &&  uniteCourante.UL != CAR)
		expectedSymbols.push_back( " type ");
	}
	else if (expected == "virg") {
	if (uniteCourante.UL != VIRG)
		expectedSymbols.push_back( " ',' ");
	}
	else if (expected == "CROVR") {
	if (uniteCourante.UL != CROOUV)
		expectedSymbols.push_back( " '[' ");
	}
	else if (expected == "CROFER") {
	if (uniteCourante.UL != CROFER)
		expectedSymbols.push_back( " ']' ");
	}
	else if (expected == "IDENT") {
	if (uniteCourante.UL != IDENT)
		expectedSymbols.push_back( " ident ");
	}
	else if (expected == "Ident") {
	if (uniteCourante.UL != IDENT)
		expectedSymbols.push_back( " ident ");
	}

	int line = lexical->getLine();
	int col = lexical->getColumn();

	if (expectedSymbols.begin() != expectedSymbols.end()) {//If we found some errors
		auto itr = syntaxErrors.find(pair<int, int>(line, col));
		if (itr != syntaxErrors.end())//We already have some errors at this position
		{
			//Appending to existing errors
			itr->second.insert(itr->second.end(),expectedSymbols.begin(), expectedSymbols.end());
		}
		else {
			//We add it to the errors map (tree)
			syntaxErrors.insert(pair< pair<int, int>,vector<string> > (pair<int, int>(line, col), expectedSymbols));
		}
	}
	else {
		//Xml pour les terminaux
		ConsoleHandler::logDebug("Syntaxique","Consumed " + expected + " at Ln" + to_string(line) + ",Col " + to_string(col));
		xmlFile << expected << " "; //espace pour éviter de concatener deux terminaux consécutifs
		uniteCourante = lexical->uniteSuivante();
	}
	
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
		return uniteCourante.UL == CROOUV;
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
		return estPremierDe(eComparaison) == true || estSuivantDe(production);;
		break;
	case eExpressionSimple:
		return uniteCourante.UL == CONST || uniteCourante.UL == CONSTCAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE
			|| uniteCourante.UL == NON || uniteCourante.UL == SOUS || uniteCourante.UL == IDENT;
		break;
	case eExpressionSimplePrime:
		return uniteCourante.UL == ADD || uniteCourante.UL == SOUS || estSuivantDe(production);
		break;
	case eTerme:
		return estPremierDe(eFacteur);
		break;
	case eTermePrime:
		return uniteCourante.UL == MUL || uniteCourante.UL == DIV || estSuivantDe(production);
		break;
	case eTermePrioritaire:
		return estPremierDe(eTerme) || uniteCourante.UL == NON;
		break;
	case eFacteur:
		return uniteCourante.UL == CONST || uniteCourante.UL == CONSTCAR || uniteCourante.UL == PAROUV || uniteCourante.UL == QUOTE
			|| uniteCourante.UL == IDENT;
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
	case eParametres:
		return uniteCourante.attribut == ENTIER || uniteCourante.UL == CAR || estSuivantDe(eParametres);
		break;
	case eParametresPrime:
		return uniteCourante.UL == VIRG;
		break;
	case eParametre:
		return uniteCourante.UL == ENTIER || uniteCourante.UL == CAR;
		break;
	case eListeInstructions:
		return estSuivantDe(eListeInstructions) || estSuivantDe(eExpression) || estPremierDe(eExpression) || uniteCourante.UL == IDENT
			|| uniteCourante.UL == RETOUR || uniteCourante.UL == SI || uniteCourante.UL == TANTQUE || uniteCourante.UL == MOTCLE;
		break;
	case eInstruction:
		return estPremierDe(eExpression) || uniteCourante.UL == IDENT || uniteCourante.UL == RETOUR || uniteCourante.UL == MOTCLE
			|| uniteCourante.UL == SI || uniteCourante.UL == TANTQUE || uniteCourante.UL == LIRE || uniteCourante.UL == ECRIRE;
		break;
	case eInstructionPrime:
		return uniteCourante.UL == EGAL || uniteCourante.UL == CROOUV;
		break;
	case eInstructionSeconde:
		return uniteCourante.UL == SINON || estSuivantDe(production);
		break;
	case eInstructionTriple:
		return estPremierDe(eExpression) || uniteCourante.UL == LIRE;
		break;

	default:
		cout << "Production non reconnue" << endl;
		break;
	}
	return false;
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
		return uniteCourante.UL == IDENT || uniteCourante.UL == MAIN;
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
		return uniteCourante.UL == PARFERM;
		break;
		//outidrarine finishes

		//souhail starts
	case eExpressionLogique:
		return estSuivantDe(eExpression) == true || uniteCourante.UL == ET || uniteCourante.UL == OU;
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
		return estSuivantDe(eTerme) == true || uniteCourante.UL == MUL || uniteCourante.UL == DIV;
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
			|| estSuivantDe(eParametre) || estSuivantDe(eDeclarationSeconde) || uniteCourante.UL == PAROUV;
	case eCte:
		return estSuivantDe(eFacteur);
		//end zac

		//start testoxe
	case eParametres:
		return uniteCourante.UL == PARFERM;
		break;
	case eParametresPrime:
		return uniteCourante.UL == PARFERM;
		break;
	case eParametre:
		return uniteCourante.UL == VIRG || uniteCourante.UL == PARFERM;
		break;
	case eListeInstructions:
		return uniteCourante.UL == ACCFERM;
		break;
	case eInstruction:
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionPrime:
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionSeconde:
		return uniteCourante.UL == PTVRG;
		break;
	case eInstructionTriple:
		return uniteCourante.UL == PTVRG;
		break;
	case eExpression:
		return uniteCourante.UL == VIRG || uniteCourante.UL == ALORS || uniteCourante.UL == FAIRE || uniteCourante.UL == CROFER
			|| uniteCourante.UL == ACCFERM || uniteCourante.UL == PTVRG || uniteCourante.UL == PARFERM;
	case eExpressionPrime:
		return uniteCourante.UL == VIRG || uniteCourante.UL == ALORS || uniteCourante.UL == FAIRE || uniteCourante.UL == CROFER
			|| uniteCourante.UL == ACCFERM || uniteCourante.UL == PTVRG || uniteCourante.UL == PARFERM;
	default:
		logError("Production non reconnue");
		break;
	}
	return false;
}

void Syntaxique::syntaxError(Production prod) {
	string message = lexical->inputFilename + " at Ln" + to_string(lexical->getLine()) + ",Col " + to_string(lexical->getColumn()) + ": error : expected ";
	switch (prod)
	{
	case eProgramme:
	case eListeDeFonctions:
	case eListeDeDeclarations:
	case eDeclaration:
	case eDeclarations:
	case eListeParametres:
	case eParametres:
	case eParametre:
		message += " type ";
		break;
	case eFonction:
	case eDeclarationPrime:
	case eOperateurLogique:
	case eComparaison:
		message += " an indentificator ";
		break;
	case eListeInstructions:
	case eInstruction:
	case eExpressionPrime:
	case eExpression:
	case eInstructionTriple:
	case eInstructionPrime:
		message += " an operator";
		break;
	case eDeclarationsPrime:
		message += " ',' ";
		break;
	case eDeclarationSeconde:
		message += " '[' ";
			break;
	case eExpressionLogique:
		message += " logic expression ";
		break;
	case eExpressionLogiquePrime:
		message += " logic operator ";
		break;
	case eExpressionSimple:
		message += " constant ";
		break;
	case eExpressionSimplePrime:
		message += " arithmetic operator ";
		break;
	case eTerme:
		message += " constant ";
		break;
	case eTermePrime:
		message += " '*' or '/' ";
		break;
	case eTermePrioritaire:
		message += " '!'  or ident or '('";
		break;
	case eFacteur:
		message += " const or '(' ";
		break;
	case eFacteurPrime:
		message += " '[' or '(' ";
		break;
	case eParametresEffectifs:
		message += " '*' or '/' ";
		break;
	case eExpressions:
		message += " '-' or '!' or const or '(' ";
		break;
	case eExpressionsPrime:
		message += " ',' ";
		break;

	case eIdentificateur:
		message += " logic operator ";
		break;
	case eCte:
		message += " const ";
		break;
	case eParametresPrime:
		message += " ',' ";
		break;
	case eInstructionSeconde:
		message += " 'sinon' ";
		break;
	case eEnd:
			return;
	default:
		logError("Erreur de production " + to_string(prod) + " non gérée par le compilateur");
		break;
	}
	message += " .";
	syntaxErrors.insert(pair<string, pair<int, int>>(message, pair<int, int>(lexical->getLine(), lexical->getColumn())));
}

void Syntaxique::logDebug(string message)
{
	if (lexical->enableDebug)//ugly but doing fine
		ConsoleHandler::logDebug("Syntaxique" , message);
}

void Syntaxique::logError(string error)
{
	ConsoleHandler::logError("Syntaxique",error);
}


//Destructeur
Syntaxique::~Syntaxique()
{
	end();
}