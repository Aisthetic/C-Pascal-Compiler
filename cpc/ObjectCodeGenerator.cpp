#include "ObjectCodeGenerator.h"
#include "ConsoleHandler.h"
#include "Constants.h"
#include "map"
#include <filesystem>
using namespace std;

ObjectCodeGenerator::ObjectCodeGenerator(string fileName)
{
	this->fileName = fileName;
	setupOutputStream();
}

void ObjectCodeGenerator::end()
{
	output.close();
	//detecting labels and functions adresses
	map<string, int> adresses;//les adresses des labels <adresse, label>
	input.open(PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName + ".o");
	int noLine = 0, nbLabels = 0;//we are going to delete labels which changes function adresse
	//by -nbLabels before it
	for (std::string line; getline(input, line); )
	{
		std::string delimiter = " ";
		auto position = line.find(delimiter);
		std::string token = line.substr(0, position);

		if (token == ENTREE) { // adresse d'une fonction
			token = line.substr(position);
			adresses.insert(adresses.begin(), pair<string, int>(token, noLine - nbLabels));
		}

		if (token == LABEL) { // adresse d'un label
			token = line.substr(position);
			adresses.insert(adresses.begin(), pair<string, int>(token, noLine - nbLabels));
			nbLabels++;
		}
		noLine++;

	}
	input.close();

	//replacing labels
	ofstream temp(PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName);
	if (!temp.is_open()) {
		return;
	}
	input.open(PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName + ".o");
	for (std::string line; getline(input, line); )
	{
		//replacing labels on appel
		if (line.find(APPEL) != string::npos)
		{
			std::string delimiter = " ";
			auto position = line.find(delimiter);
			std::string funcName = line.substr(position);
			line.replace(APPEL.length() + 1, line.length(), to_string(adresses[funcName]));
		}
		//replacing labels on sifaux
		if (line.find(SIFAUX) != string::npos) {
			std::string delimiter = " ";
			auto position = line.find(delimiter);
			std::string labelName = line.substr(position);
			line.replace(SIFAUX.length() + 1, line.length(), to_string(adresses[labelName]));
		}
		//deleting labels on entree
		if(line.find(ENTREE) != string::npos)
			line.replace(ENTREE.length(), line.length(), "");
		//replacing labels
		if (line.find(LABEL) != string::npos)
			line.replace(0, line.length(), "");
		if(line != "")
			temp << line << endl;
	}
	input.close();
	temp.close();
	int result  = remove((PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName + ".o").c_str());
	result = rename((PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName).c_str(), (PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName + ".o").c_str());
}

ObjectCodeGenerator::ObjectCodeGenerator()
{
	this->fileName = "";
}

void ObjectCodeGenerator::empc(int constante)
{
	output << EMPC << ' ' << constante << endl;
}


void ObjectCodeGenerator::stop()
{
	output << STOP << endl;
}

void ObjectCodeGenerator::add()
{
	output << ADD << endl;
}

void ObjectCodeGenerator::mul()
{
	output << MUL << endl;
}

void ObjectCodeGenerator::sous()
{
	output << SOUS << endl;
}

void ObjectCodeGenerator::non()
{
	output << NON << endl;
}

void ObjectCodeGenerator::empg(int adresse)
{
	output << EMPG << " " << adresse << endl;
}

void ObjectCodeGenerator::empl(int adresse)
{
	output << EMPL << " " << adresse << endl;
}

void ObjectCodeGenerator::depg(int adresse)
{
	output << DEPG << " " << adresse << endl;
}

void ObjectCodeGenerator::depl(int adresse)
{
	output << DEPL << " " << adresse << endl;
}

void ObjectCodeGenerator::ecriv()
{
	output << ECRIV << endl;
}

void ObjectCodeGenerator::lire()
{
	output << LIRE << endl;
}

void ObjectCodeGenerator::pile(int nbrMots)
{
	output << PILE << " " << nbrMots << endl;
}

void ObjectCodeGenerator::saut(string label) {
	output << SAUT << " " << label << endl;
}

void ObjectCodeGenerator::label(string nom) {
	output << LABEL << " " << nom << endl;
}

void ObjectCodeGenerator::sifaux(string label) {
	output << SIFAUX << " " << label << endl;
}

void ObjectCodeGenerator::comp(string oper)
{
	output << oper << endl;
}

void ObjectCodeGenerator::fin()
{
	output << FIN << endl;
}

//L'appel de fonction est fait par son nom en premier lieu
//puisqu'on connait pas son adresse puis on remplace les noms
//par les adresse quand on finit la generation de code
void ObjectCodeGenerator::appel(string fonction)
{
	output << APPEL << " " << fonction << endl;
}

void ObjectCodeGenerator::retour()
{
	output << RETOUR << endl;
}

void ObjectCodeGenerator::entree()
{
	output << ENTREE << endl;
}

void ObjectCodeGenerator::entree(string name)
{
	output << ENTREE << " " << name << endl;
}

void ObjectCodeGenerator::sortie()
{
	output << SORTIE << endl;
}

void ObjectCodeGenerator::div()
{
}

ObjectCodeGenerator::~ObjectCodeGenerator()
{
	output.flush();// pousser toujours la chasse avant de sortir
}

void ObjectCodeGenerator::setupOutputStream()
{
	if (!output.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		output.open(PMACHINE_CODE_OUTPUT_DIRECTORY + "/" + fileName + ".o");
		if (!output.is_open()) {
			ConsoleHandler::logError("CodeGenerator","Impossible d'ouvrir le fichier d'output de la generation de code");
			return;
		}
	}
}
