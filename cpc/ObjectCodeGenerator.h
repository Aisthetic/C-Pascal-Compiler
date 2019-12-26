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
	const string ADD = "ADD";
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
	void evriv();
	void stop();
	void add();
	~ObjectCodeGenerator();
};

