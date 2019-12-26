#include "ObjectCodeGenerator.h"
#include "ConsoleHandler.h"

ObjectCodeGenerator::ObjectCodeGenerator(string fileName)
{
	this->fileName = fileName;
}

ObjectCodeGenerator::ObjectCodeGenerator()
{
	this->fileName = "";
}

void ObjectCodeGenerator::empc(int constante)
{
	output << EMPC << ' ' << constante << endl;
}

void ObjectCodeGenerator::evriv()
{
	output << ECRIV << endl;
}

void ObjectCodeGenerator::stop()
{
	output << STOP << endl;
}

void ObjectCodeGenerator::add()
{
	output << ADD << endl;
}

ObjectCodeGenerator::~ObjectCodeGenerator()
{
	output.flush();// pousser toujours la chasse avant de sortir
}

void ObjectCodeGenerator::setupOutputStream()
{
	if (!output.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		output.open( fileName + ".o");
		if (!output.is_open()) {
			ConsoleHandler::logError("CodeGenerator","Impossible d'ouvrir le fichier d'output de la generation de code");
			return;
		}
	}
}
