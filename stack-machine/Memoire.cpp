#include "Memoire.h"

Memoire::Memoire(vector<string> code)
{
	// Copying code to its place on the memory
	std::copy(code.begin(), code.end(), cells.begin());

	// Changing registers accordingly
	beg = code.max_size; //         has to add global variables handling !!!!!!!!!!
	bel = code.max_size;
	sp = code.max_size;
}

bool Memoire::isFull()
{
	if (sp >= memorySize) { return true; } 
	else { return false; }
	
}

void Memoire::empc(string value)
{
	if (isFull()) {
		cout << "Overflow de la pile !";
		//stop();    has to stop execution !!!!!!!!!
		return;
	}
	else {
		cells[sp] = value;
		sp++;
	}
}

void Memoire::depl(int adress)
{

}

void Memoire::addi()
{
	if (sp <= beg + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer l'addition !";
	;}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(cells[sp - 1]);
		sp--;
		// Popping out second term
		int t2 = stoi(cells[sp - 2]);
		sp--;

		// Stacking the addition
		Memoire::empc(to_string(t1 + t2));
	}
}

void Memoire::sous()
{
	if (sp <= beg + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la soustraction !";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(cells[sp - 1]);
		sp--;
		// Popping out second term
		int t2 = stoi(cells[sp - 2]);
		sp--;

		// Stacking the substraction
		empc(to_string(t2 - t1));
	}
}

void Memoire::dup()
{
	if (sp <= beg + 1) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la duplication !";
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
	}
}
