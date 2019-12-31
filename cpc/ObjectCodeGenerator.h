#pragma once
#include <fstream> 

using namespace std;

class ObjectCodeGenerator
{
private:
	//constants
	const string EMPC = "EMPC";
	const string ECRIV = "ECRIV";
	const string ECRIC = "ECRIC";
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
	const string EMPT = "EMPT";
	const string NON = "NON";
	const string EMPL = "EMPL";
	const string DEPL = "DEPL";
	const string DEPG = "DEPG";
	const string DEPT = "DEPT";
	const string LIRE = "LIRE";
	const string SAUT = "SAUT";
	const string LABEL = "LABEL";
	const string SIFAUX = "SIFAUX";
	const string SIVRAI = "SIVRAI";
	const string FIN = "FIN";
	//const string = "";
	//fields
	ofstream output;
	ifstream input;//opened at the end to replace labels
	string fileName;
	//private functions
	void setupOutputStream();
public:
	//Const
	ObjectCodeGenerator();
	ObjectCodeGenerator(string fileName);

	//Public functions
	void end();

	//Generator functions
	void empc(int constante);
	void empc(char constante);
	void stop();
	void add();
	void pile(int nbrMots);
	void appel(string fonction);
	void retour();
	void entree();
	void entree(string name);
	void sortie();
	void div();
	void mul();
	void sous();
	void non();
	void empg(int adresse);
	void empt(int adresse);
	void empl(int adresse);
	void depg(int adresse);
	void dept(int adresse);
	void depl(int adresse);
	void ecriv();
	void ecric();
	void lire();
	void saut(string label);
	void label(string nom);
	void sifaux(string label);
	void sivrai(string label);
	void comp(string oper);
	void fin();
	~ObjectCodeGenerator();
};

