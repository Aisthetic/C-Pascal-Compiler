#pragma once
#include <string>
#include <map>
using namespace std;
typedef enum
{
	PTVRG, // ;
	VIRG, // ,
	ACCOUV, // {
	ACCFERM, // }
	PAROUV, // (
	PARFERM, // )
	CROOUV, // [
	CROFER, // ]
	ET, // &
	OU, // |
	ADD, // +
	SOUS, // -
	MUL, // *
	DIV, // /
	INFEGAL, // <=
	INF, // <
	EGAL, // =
	
	NONEGAL, // !=
	NON, // !
	SUPEGAL, // >=
	SUP, // >
	CONST, // Constante entiere comme 3
	CONSTCAR, //Constante caractere comme 'a'
	MOTCLE, // MOT RESERVE
	IDENT, // IDENTIFIANT
	CAR, // Type caractere
	ENTIER, //Type eniter
	ERR, //Erreur
	END, //fin de fichier
	MAIN, // main
	QUOTE,// '

	EGALEGAL, // ==  to aaaaaaddddddddddddd


	// Mots reserves
	// to add too ---------/\------------
	SI,
	SINON,
	ALORS,
	TANTQUE,
	FAIRE,
	RETOUR,

	// 
	LIRE,
	ECRIRE,
} TUnite;

//Tfo ela hayat
//const std::map<int, string> TUniteToString = {
//	{PTVRG,"Point virgule"},
//	{VIRG,"virgule"},
//	{ACCOUV,"accolade ouvrante"},
//	{ACCFERM,""},
//	{PAROUV,},
//	{PARFERM,},
//	{CROOUV,},
//	{CROFER,},
//	{ET,},
//	{OU,},
//	{ADD,},
//	{SOUS,},
//	{MUL,},
//	{DIV,},
//	{,},
//	 
//};

typedef enum//on ajoute le e pour �viter la confusion entre les fonctions et les enums pour le compilateur
{
	eProgramme,
	eDeclarations,
	eDeclarationsPrime,
	eListeDeDeclarations,
	eDeclaration,
	eDeclarationPrime,
	eDeclarationSeconde,
	eListeParametres,
	eListeDeFonctions,
	eFonction,
	eIdentificateur,
	eLettre,
	eCaractere,
	eExpression,
	eParametre,
	eExpressionPrime,
	eOperateurLogique,
	eComparaison,
	eExpressions,
	eFacteur,
	eCte,
	eParametres,
	eParametresPrime,
	eListeInstructions,
	eInstruction,
	eInstructionPrime,
	eInstructionTriple,
	eInstructionSeconde,
	eExpressionLogique,
	eTermePrioritaire,
	eTerme,
	eExpressionSimple,
	eExpressionLogiquePrime,
	eExpressionSimplePrime,
	eTermePrime,
	eFacteurPrime,
	eExpressionsPrime,
	eParametresEffectifs,
	eEnd,
} Production;

typedef struct TUniteLexicale
{
	TUnite UL;
	int attribut;
} TUniteLexicale;


//Regroupe les données d'une production
template <int N,int M> struct ProductionData {
	Production prod;
	string name;
	Production premiers[N];
	Production suivants[M];
};

