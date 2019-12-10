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
	string inputFilename;//avec extension
	char currentChar; //le charactère courant
	Hashage motsReserves; //contenaire des mots reserve
	//streams
	ifstream input;//peut être fichier,string dans la console..etc
	ofstream output;//lexical output stream
	ofstream identifOutput;//identif table 
	ofstream motsResOutput;//mots res table
	//methods
	bool estBlanc(char);
	bool lireCar();//bool pour verifier si on peut toujours lire
	void initierMotsReserves();
	void lexemeToString(TUniteLexicale);
	bool estChiffre(); // prend le caractère courant est vérifie s'il est chiffre
	bool estCaractere(); //prend la caractère courant est vérifie s'il est caractère 
	bool enableDebug; //true if you want to see debug outputffffffffffffffffffffffffff
	void logDebug(string);
	void logError(string);
	friend class Syntaxique;
public:
	Hashage identifiants; //table des identifiants //todo getter
	//const & des
	Lexical(bool debug = false);
	Lexical(string file,bool debug, bool logTableIdentifs , bool logTableMotsRes );
	~Lexical();
	//methods
	TUniteLexicale uniteSuivante();
	void processAllFile(); //fonction test
	void setupOutput();//pour ouvrir l'output en cas de besoin
	void setupIdentifsOutput();
	void setupMotsResOutput();
	//getters & setters
	void setInput(string file, bool logTableIdentifs, bool logTableMotsRes );
	string getInputFileNameWithoutExt();
};

