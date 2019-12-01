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
	eParametres,
	eParametresPrime,
	eParametre,
	eListeInstructions,
	eInstruction,
	eInstructionPrime,
	eInstructionTriple,
	eInstructionSeconde,
	eExpressionLogique,
	eOperateurLogique,
	eExpressionPrime,
} Production;

typedef struct TUniteLexicale
{
	TUnite UL;
	int attribut;
} TUniteLexicale;