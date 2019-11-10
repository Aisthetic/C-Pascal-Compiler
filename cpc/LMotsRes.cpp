#include "LMotsRes.h"

LMotsRes::LMotsRes()
{
	this->listeMotsRes.push_back( new MotReserve("entier", entier) );
	this->listeMotsRes.push_back(new MotReserve("si", si));
	this->listeMotsRes.push_back(new MotReserve("alors", alors));
	this->listeMotsRes.push_back(new MotReserve("sinon", sinon));
	this->listeMotsRes.push_back(new MotReserve("tantque", tantque));
	this->listeMotsRes.push_back(new MotReserve("faire", faire));
	this->listeMotsRes.push_back(new MotReserve("retour", retour));
	this->listeMotsRes.push_back(new MotReserve("ecrire", ecrire));
	this->listeMotsRes.push_back(new MotReserve("lire", lire));
	this->listeMotsRes.push_back(new MotReserve("Car", car));
	this->listeMotsRes.push_back(new MotReserve("main", main));
}

int LMotsRes::isMotRes(std::string mot)
{
	// Iterateur pour parcourir la list
	std::list<MotReserve *>::iterator it;

	// Parcours de la liste pour voir si le mot est réservé 
	for (it = listeMotsRes.begin(); it != listeMotsRes.end(); it++) {
		if ((*it)->getLexeme() == mot) {
			return (*it)->getUniteLexical();
		}
	}
	return -1;
}
