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
	END //fin de fichier
} TUnite;

typedef enum//on ajoute le e pour éviter la confusion entre les fonctions et les enums pour le compilateur
{
	eProgramme,
	eListeDeDeclarations,
	eDeclaration,
	eListeDeFonctions,
	eFonction,
	eIdentificateur,
	eLettre,
	eCaractere,
	eListeDeDeclarationsPrime,
	eExpression,
	eParametre,
	eExpressionPrime,
	eOperateurLogique,
	eComparaison,
	eIdentif,
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
} Production;

typedef struct TUniteLexicale
{
	TUnite UL;
	int attribut;
} TUniteLexicale;