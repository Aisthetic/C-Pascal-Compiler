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

void Memoire::empc(string value)
{
	if (stackFull()) {
		cout << "Overflow de la pile !\n";
		//stop();    has to stop execution !!!!!!!!!
		return;
	}
	else {
		cells[sp] = value;
		sp++;
		cout << "Done.\n";
	}
}

void Memoire::depl(int adress)
{

}

void Memoire::addi()
{
	if (sp <= beg + 2) {
		cout << "sp =" << sp << "and beg = " << beg;
		cout << "Cellules insuffisantes dans la pile pour effectuer l'addition !\n";
	;}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(cells[sp - 1]);
		sp--;
		cout << t1 << " + ";
		// Popping out second term
		int t2 = stoi(cells[int(sp - 1)]);
		sp--;
		cout << t2 << " = ";

		// Stacking the addition
		cout << t1 + t2 << ". ";
		Memoire::empc(to_string(t1 + t2));
		
	}
}

void Memoire::sous()
{
	if (sp <= beg + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la soustraction !\n";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(cells[sp - 1]);
		sp--;
		cout << t1 << " - ";
		// Popping out second term
		int t2 = stoi(cells[sp - 1]);
		sp--;
		cout << t2 << " = ";

		// Stacking the substraction
		cout << t1 - t2 << ". ";
		empc(to_string(t2 - t1));
		
	}
}

void Memoire::dup()
{
	if (sp <= beg + 1) {
		cout << "sp =" << sp << "and beg = " << beg;
		cout << "Cellules insuffisantes dans la pile pour effectuer la duplication !\n";
	}
	else {
		// Popping out stack
		string value = cells[sp - 1];
		sp--;

		// Stacking twice
		cells[sp] = value;
		sp++;
		cells[sp] = value;
		sp++;
		cout << "Done.\n";
	}
}

int Memoire::getCo()
{
	return co;
}

string Memoire::getCell(int num)
{
	return cells[num];
}

void Memoire::ecriv()
{
	if (stackEmpty()) {
		cout << "Pile vide !";
	}
	else {
		// Popping out stack
		string value = cells[sp - 1];
		sp--;

		// Writing to console
		cout << value;

		// Stacking the value again
		cells[sp] = value;
		sp++;
	}
}

void Memoire::incCo()
{
	co++;
}

void Memoire::setCo(int toSet)
{
	co = toSet;
}
