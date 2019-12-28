#include "ObjectCodeGenerator.h"
#include "ConsoleHandler.h"
#include "Constants.h"

ObjectCodeGenerator::ObjectCodeGenerator(string fileName)
{
	this->fileName = fileName;
	setupOutputStream();
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

void ObjectCodeGenerator::pile(int nbrMots)
{
	output << PILE << " " << nbrMots << endl;
}

//L'appel de fonction est fait par son nom en premier lieu
//puisqu'on connait pas son adresse puis on remplace les noms
//par les adresse quand on finit la generation de code
void ObjectCodeGenerator::appel(string fonction)
{
	output << APPEL << " #" << fonction << endl;
}

void ObjectCodeGenerator::retour()
{
	output << RETOUR << endl;
}

void ObjectCodeGenerator::entree()
{
	output << ENTREE << endl;
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
