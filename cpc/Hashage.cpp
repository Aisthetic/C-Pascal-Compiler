#include <iostream>
#include <string>
#include "Hashage.h"
#include <math.h>
using namespace std;
Hashage::Hashage()
{
	for (int i = 0; i < TABLESIZE; i++)
	{
		HashTable[i] = new item;
		HashTable[i]->data = "";
		HashTable[i]->next = NULL;
	}
}

void Hashage::ajouter(string data)
{

	int index = Hash(data);

	if (HashTable[index]->data == "")
	{
		HashTable[index]->data = data;
	}
	else
	{
		collisions++;
		item* Ptr = HashTable[index];
		item* n = new item;
		n->data = data;
		n->next = NULL;
		while (Ptr->next != NULL)
		{
			Ptr = Ptr->next;
		}
		Ptr->next = n;
	}
}
int Hashage::nombreDesNoeuds(int index)
{
	int count = 0;

	if (HashTable[index]->data == "")
	{
		return count;
	}
	else
	{
		count++;
		item* Ptr = HashTable[index];
		while (Ptr->next != NULL)
		{
			count++;
			Ptr = Ptr->next;
		}
	}
	return count;
}
void Hashage::afficher()
{
	int number;
	for (int i = 0; i < TABLESIZE; i++)
	{
		number = nombreDesNoeuds(i);
		cout << "\nindice = " << i << endl;

		if (number > 1)
		{
			afficherNoeuds(i);
			cout << "\t\tnombre des noeuds = " << number << endl;
		}
		else {
			cout << "\t\t" << HashTable[i]->data << endl;
			cout << "\t\tnombre des noeuds = " << number << endl;
		}
	}
	cout << "numero des collisions: " << collisions << endl;
}
void Hashage::afficherNoeuds(int index)
{
	item* Ptr = HashTable[index];

	if (Ptr->data == "")
	{
		// silence is golden --Echblaoui
	}
	else
	{
		while (Ptr != NULL)
		{
			cout << "\t\t" << Ptr->data << endl;
			Ptr = Ptr->next;
		}

	}
}
bool Hashage::supprimer(string name)
{
	int index = Hash(name);

	item* delPtr;
	item* P1;
	item* P2;

	if (existe(name) == -1)// précondition
		return false; //non trouvé

	//Case 0 - seau vide
	if (HashTable[index]->data == "")
	{
		return false; // non trouvé
	}
	//Case 2 - un seul item dans le seau et c'est le item correspendant
	else if (HashTable[index]->data == name && HashTable[index]->next == NULL)
	{
		HashTable[index]->data = "";
		return true; // très bien
	}
	//Case 3 - l'info existe dans le premier item du seau et il existe d'autres items dans le seau
	else if (HashTable[index]->data == name)
	{
		delPtr = HashTable[index];
		HashTable[index] = HashTable[index]->next;
		delete delPtr;
		collisions--;
		return true; // très bien
	}
	//Case 3 - le seau contient des items et le premier item n'est pas le correspendant
	else
	{
		P1 = HashTable[index]->next;
		P2 = HashTable[index];
		while (P1 != NULL && P2->data != name)
		{
			P2 = P1;
			P1 = P1->next;
		}
		if (P1 == NULL)
		{
			return false; // non trouvé
		}
		else
		{
			delPtr = P1;
			P1 = P1->next;
			delete delPtr;
			collisions--;
			return true; // très bien
		}

	}
}

int Hashage::Hash(string key) // hashage par la méthode polynomiale et compression par methode de la division
{
	int hash1 = 0;
	int index;
	int coef = 42;
	for (int i = 0; i < key.length(); i++)
	{
		hash1 = hash1 + ((int)key[i]) * (pow(coef, i));
	}
	index = hash1 % TABLESIZE;
	return index;
}
int Hashage::existe(string info)
{
	int index = Hash(info);

	item* delPtr;
	item* P1;
	item* P2;

	//Case 0 - seau vide
	if (HashTable[index]->data == "")
	{
		return -1;
	}
	//Case 1 - un seul intem dans le deau, et c'est le intem correspendant
	else if (HashTable[index]->data == info)
	{
		return index;
	}
	//Case 2 - le seau contient des items et le premier n'est pas le correspendant
	else
	{
		P1 = HashTable[index]->next;
		P2 = HashTable[index];
		while (P1 != NULL && P2->data != info)
		{
			P2 = P1;
			P1 = P1->next;
		}
		if (P1 == NULL)
		{
			return -1;
		}
		else
		{
			return index;
		}

	}
}