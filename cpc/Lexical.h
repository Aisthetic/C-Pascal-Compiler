#pragma once
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Hashage.h"
using namespace std;
class Lexical
{
private:
	//fields
	ifstream input;//peut �tre fichier,string dans la console..etc
	ofstream output;
	char currentChar; //le charact�re courant
	Hashage motsReserves; //contenaire des mots reserve
	Hashage indetifs; //table des identifiants
	//methods
	bool estBlanc(char);
	bool lireCar();//bool pour verifier si on peut toujours lire
	void initierMotsReserves();
	
public:
	//const & des
	Lexical();
	~Lexical();
	//methods
	TUniteLexicale uniteSuivante();
	bool estChiffre(); // prend le caract�re courant est v�rifie s'il est chiffre
	bool estCaractere(); //prend la caract�re courant est v�rifie s'il est caract�re 
	void processAllFile(); //fonction test
	//getters & setters
	void setInput(string);
};

