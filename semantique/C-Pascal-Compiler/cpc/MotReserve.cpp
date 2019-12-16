#include "MotReserve.h"

MotReserve::MotReserve(std::string lexeme, int uniteLexical)
{
	this->lexeme = lexeme;
	this->uniteLexical = uniteLexical;
}

std::string MotReserve::getLexeme()
{
	return this->lexeme;
}

int MotReserve::getUniteLexical()
{
	return this->uniteLexical;
}
