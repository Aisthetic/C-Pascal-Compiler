#pragma once
#include <string>
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
	EGALEGAL, // ==
	NONEGAL, // !=
	NON, // !
	SUPEGAL, // >=
	SUP, // >
	CONST, // CONST
	MOTCLE, // MOT RESERVE
	IDENT, // IDENTIFIANT
	CAR, // Caractere
	ERR, //Erreur
	END, //fin de fichier
	ENTIER, //eniter
	REAL, //real
	MAIN, // main
	DOLAR,//$
	QUOTE,// '
} TUnite;

typedef enum//on ajoute le e pour �viter la confusion entre les fonctions et les enums pour le compilateur
{
	eProgramme,
	eDeclarations,
	eDeclarationsPrime,
	eListeDeDeclarations,
	eListeDeDeclarationsPrime,
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
	eOperateurLogique,
	eExpressionPrime,
	eTermePrioritaire,
	eTerme,
	eExpressionSimple,
	eExpressionLogiquePrime,
	eExpressionSimplePrime,
	eTermePrime,
	eFacteurPrime,
	eExpressionsPrime,
	eParametresEffectifs,
} Production;

typedef struct TUniteLexicale
{
	TUnite UL;
	int attribut;
} TUniteLexicale;