#pragma once
#include <fstream> 

using namespace std;

class ObjectCodeGenerator
{
private:
	//constants
	const string EMPC = "EMPC";
	const string ECRIV = "ECRIV";
	const string STOP = "STOP";
	const string PILE = "PILE";
	const string APPEL = "APPEL";
	const string RETOUR = "RETOUR";
	const string ENTREE = "ENTREE";
	const string SORTIE = "SORTIE";
	const string ADD = "ADD";
	const string SOUS = "SOUS";
	const string MUL = "MUL";
	const string DIV = "DIV";
	const string EMPG = "EMPG";
	const string NON = "NON";
	const string EMPL = "EMPL";
	const string DEPL = "DEPL";
	const string DEPG = "DEPG";
	const string LIRE = "LIRE";
	const string SAUT = "SAUT";
	const string LABEL = "LABEL";
	const string SIFAUX = "SIFAUX";
	//const string = "";
	//fields
	ofstream output;
	string fileName;
	//private functions
	void setupOutputStream();
public:
	//Const
	ObjectCodeGenerator();
	ObjectCodeGenerator(string fileName);

	//Public functions

	//Generator functions
	void empc(int constante);
	void stop();
	void add();
	void pile(int nbrMots);
	void appel(string fonction);
	void retour();
	void entree();
	void sortie();
	void div();
	void mul();
	void sous();
	void non();
	void empg(int adresse);
	void empl(int adresse);
	void depg(int adresse);
	void depl(int adresse);
	void ecriv();
	void lire();
	void saut(string label);
	void label(string nom);
	void sifaux(string label);
	void comp(string oper);
	~ObjectCodeGenerator();
};

