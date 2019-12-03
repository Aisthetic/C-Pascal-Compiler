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