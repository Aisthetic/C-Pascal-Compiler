#include "Memoire.h"

Memoire::Memoire(vector<string> code)
{
	// Copying code to its place on the memory
	std::copy(code.begin(), code.end(), cells.begin());

	// Changing registers accordingly
	beg = code.size(); //         has to add global variables handling !!!!!!!!!!
	bel = code.size();
	sp = code.size()+1;
}

bool Memoire::stackFull()
{
	if (sp >= MEMORYSIZE) { return true; } 
	else { return false; }
	
}

bool Memoire::stackEmpty()
{
	if (sp <= beg + 1) { return true; }
	else { return false; }
}

int Memoire::getCo()
{
	return co;
}

int Memoire::getBeg()
{
	return beg;
}

int Memoire::getBel()
{
	return bel;
}

int Memoire::getSp()
{
	return sp;
}

string Memoire::getCell(int num)
{
	return cells[num];
}

void Memoire::incCo()
{
	co++;
}

void Memoire::incSp()
{
	sp++;
}

void Memoire::decSp()
{
	sp--;
}

void Memoire::setCo(int toSet)
{
	co = toSet;
}

void Memoire::setCell(int num, string value)
{
	cells[num] = value;
}
