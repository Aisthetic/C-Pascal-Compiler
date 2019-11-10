#pragma once

#include "MotReserve.h"
#include "list"

// Gestion de la liste des mots r�serv�s
class LMotsRes
{
	// Dictionnaire Unit� lexicale avec l'entier qui correspond
	enum UniLex {
		entier = 0,
		si = 1,
		alors = 2,
		sinon = 3,
		tantque = 4,
		faire = 5,
		retour = 6,
		ecrire = 7,
		lire = 8,
		car = 9,
		main = 10,
	};

	// Liste des mots r�serv�s
	std::list<MotReserve *> listeMotsRes;
public:
	LMotsRes();
	int isMotRes(std::string mot);

};

