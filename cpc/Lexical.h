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
	string inputFilename;
	ifstream input;//peut être fichier,string dans la console..etc
	ofstream output;
	char currentChar; //le charactère courant
	Hashage motsReserves; //contenaire des mots reserve
	//methods
	bool estBlanc(char);
	bool lireCar();//bool pour verifier si on peut toujours lire
	void initierMotsReserves();
	void lexemeToString(TUniteLexicale);
	bool estChiffre(); // prend le caractère courant est vérifie s'il est chiffre
	bool estCaractere(); //prend la caractère courant est vérifie s'il est caractère 
	bool logDebug; //true if you want to see debug outputffffffffffffffffffffffffff
public:
	Hashage identifiants; //table des identifiants //todo getter
	//const & des
	Lexical();
	~Lexical();
	//methods
	TUniteLexicale uniteSuivante();
	void processAllFile(); //fonction test
	//getters & setters
	void setInput(string);
};

