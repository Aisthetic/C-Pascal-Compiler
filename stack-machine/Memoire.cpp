#include "Memoire.h"

Memoire::Memoire(vector<string> code)
{
	// Copying code to its place on the memory
	std::copy(code.begin(), code.end(), cells.begin());

	// Changing registers accordingly
	beg = (int)code.size();
	bel =(int) code.size();
	sp = (int)code.size() + 1;
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

int Memoire::getStCellNum(int cell)
{
	return cell - beg - varGloNum - 2;
}

int Memoire::getVarGloNum()
{
	return varGloNum;
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

void Memoire::incVarGloNum()
{
	varGloNum++;
}

void Memoire::setCo(int toSet)
{
	co = toSet;
}

void Memoire::setBel(int toSet)
{
	bel = toSet;
}

void Memoire::setSp(int toSet)
{
	sp = toSet;
}

void Memoire::setCell(int num, string value)
{
	cells[num] = value;
}

void Memoire::setVarGloNum(int toSet)
{
	varGloNum = toSet;
}
