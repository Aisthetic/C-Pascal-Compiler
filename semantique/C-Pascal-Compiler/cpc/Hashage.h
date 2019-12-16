#pragma once
#include <iostream>
#include <string>
#include "Utilities.h"
#include "tableFormat.h"
using namespace std;

class Hashage
{
private:

	static const int TABLESIZE = 20;

	TextTable formattedTable;
	
	typedef struct node
	{
		string data;
		node* next;
	} node;

	node* HashTable[TABLESIZE];

	int collisions = 0;

	friend class Lexical;

public:
	
	Hashage();

	int Hash(string key); // prends une chaine de caractères et retourne son indice

	void ajouter(string data); //prends une chaine de caractère et l'ajoute dans notre table

	int nombreDesNoeuds(int index); // prends un indice d'un noeud et retourne combient de noeuds y existe

	TextTable afficher(); // affichage de la table pour soucis de débougage

	void afficherNoeuds(int index); // prends un noeud et affiche son contenu et tous les noeuds qui y existe

	bool supprimer(string info); // prends un string et le supprime, retourne true si la chaine est rouvé et supprimé, false sinon

	int existe(string info); // prends une chaine de caractère et retourne son indice,  elle retourne -1 si elle n'existe pas dans la table

	string pop(int i); //retourne la chaine de caracatère qui existe dans la tête d'un noeud


};