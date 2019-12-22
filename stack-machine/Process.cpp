#include "Process.h"

Process::Process(Memoire * mem) 
{
	memoire = mem;
}


void Process::empc(string value)
{
	if (memoire->stackFull()) {
		cout << "Overflow de la pile !\n";
			//stop();
		return;
	}
	else 
	{
		memoire->setCell(memoire->getSp(), value);
		memoire->incSp();
		cout << "Empilement de " << value << " dans la cellule: " << memoire->getStCellNum(memoire->getSp()) << ".\n";
	
		// Next instruction
		memoire->incCo();
	}
}

void Process::depl(int adress)
{

}

void Process::addi()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "sp =" << memoire->getSp() << "and beg = " << memoire->getBeg();
		cout << "Cellules insuffisantes dans la pile pour effectuer l'addition !\n";
		;
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());
		cout << t1 << " + ";
		// Popping out second term
		int t2 = stoi(dep());
		cout << t2 << " = ";

		// Stacking the addition
		cout << t1 + t2 << ". ";
		emp(to_string(t1 + t2));

		// Next instruction
		memoire->incCo();
	}
}

void Process::sous()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la soustraction !\n";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());
		cout << t1 << " - ";

		// Popping out second term
		int t2 = stoi(dep());
		cout << t2 << " = ";

		// Stacking the substraction
		cout << t1 - t2 << ". ";
		emp(to_string(t1 - t2));

		// Next instruction
		memoire->incCo();
	}
}

void Process::mul()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la multiplication !\n";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());
		cout << t1 << " x ";

		// Popping out second term
		int t2 = stoi(dep());
		cout << t2 << " = ";

		// Stacking the mul
		cout << t1 * t2 << ". ";
		emp(to_string(t2 * t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::div()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la division !\n";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());
		cout << t1 << " / ";

		// Popping out second term
		int t2 = stoi(dep());
		cout << t2 << " = ";

		// Stacking the div
		cout << t1 / t2 << ". ";
		emp(to_string(t1 / t2));

		// Next instruction
		memoire->incCo();
	}
}

void Process::mod()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer le modulo !\n";
	}
	else if (false) {
		// has to Check if int or car ... should be int !!!!!!!!!!!
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());
		cout << t1 << " % ";

		// Popping out second term
		int t2 = stoi(dep());
		cout << t2 << " = ";

		// Stacking the mod
		cout << t1 % t2 << ". ";
		emp(to_string(t1 % t2));

		// Next instruction
		memoire->incCo();
	}
}

void Process::egal()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'egalite !\n";
		exit(0);
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t1 == t2) {
			cout << t1 << " == " << t2 << "\n";
			emp(to_string(1));
		}
		else {
			cout << t1 << " != " << t2 << "\n";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::inf()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'inferiorité !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t1 < t2) {
			cout << t1 << " < " << t2 << "\n";
			emp(to_string(1));
		}
		else {
			cout << t1 << " !< " << t2 << "\n";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::infeg()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'infeg !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t1 <= t2) {
			cout << t1 << " <= " << t2 << "\n";
			emp(to_string(1));
		}
		else {
			cout << t1 << " !<= " << t2 << "\n";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::non()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'infeg !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (t1) {
			cout << t1 << " == 0\n.";
			emp(to_string(1));
		}
		else {
			cout << t1 << " != 0\n.";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::lire()
{
	string toRead;
	cin >> toRead;
	emp(toRead);
}


void Process::dup()
{
	if (memoire->getSp() <= memoire->getBeg() + 1) {
		cout << "sp =" << memoire->getSp() << "and beg = " << memoire->getBeg();
		cout << "Cellules insuffisantes dans la pile pour effectuer la duplication !\n";
	}
	else 
	{
		// Popping out stack
		string value = dep();

		// Stacking twice
		emp(value);
		emp(value);

		// Next instruction
		memoire->incCo();
	}
}

void Process::pop()
{
	memoire->decSp();

	// Next instruction
	memoire->incCo();
}

string Process::dep()
{
	string cell = memoire->getCell(memoire->getSp() - 1);
	memoire->decSp();
	return cell;
}

void Process::emp(string value)
{
	if (memoire->stackFull()) {
		cout << "Overflow de la pile !\n";
		//stop();
		return;
	}
	else
	{
		memoire->setCell(memoire->getSp(), value);
		memoire->incSp();
		cout << "Empilement de " << value << " dans la cellule: " << memoire->getStCellNum(memoire->getSp()) << ".\n";
	}
}

void Process::ecriv()
{
	if (memoire->stackEmpty()) {
		cout << "Pile vide !\n";
	}
	else {
		// Popping out stack
		string value = dep();

		// Writing to console
		cout << value << ".\n";
	}

	// Next instruction
	memoire->incCo();
}

void Process::saut(int address)
{
	memoire->setCo(address);
}

void Process::sivrai(int adress)
{
	if (memoire->getSp() <= memoire->getBeg() + 1) {
		cout << "Cellules insuffisantes dans la pile pour verifier si vrai !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (!t1) {
			saut(adress);
		}
		else {
			memoire->incCo();
		}
	}
}

void Process::sifaux(int adress)
{
	if (memoire->getSp() <= memoire->getBeg() + 1) {
		cout << "Cellules insuffisantes dans la pile pour verifier si faux !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (t1) {
			saut(adress);
		}
		else {
			memoire->incCo();
		}
	}
}

void Process::appel(int adress)
{
	emp(to_string(memoire->getCo() + 1));
	saut(adress);
}

void Process::retour()
{
	int address;
	address = stoi(dep());
	saut(address);
}

void Process::entree()
{
	emp(to_string(memoire->getBel()));
	memoire->setBel(memoire->getSp());

	// Next instruction
	memoire->incCo();
}

void Process::sortie()
{
	memoire->setSp(memoire->getBeg());
	memoire->setBel(stoi(dep()));

	// Next instruction
	memoire->incCo();
}

