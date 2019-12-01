#pragma once
#include <string>

class MotReserve
{
	std::string lexeme;
	int uniteLexical;
	
public:
	MotReserve(std::string lexeme, int uniteLexical);
	std::string getLexeme();
	int getUniteLexical();
};