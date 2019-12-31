#include "Process.h"

Process::Process(Memoire * mem) 
{
	memoire = mem;
}


void Process::empc(string value)
{
	if (memoire->stackFull()) {
		cout << "Overflow de la pile !\n";
		stop();
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

void Process::empl(int address)
{
	int realAddress = address + memoire->getBel();
	string varLoc = memoire->getCell(realAddress);
	emp(varLoc);
	memoire->incCo();
}

void Process::depl(int address)
{
	int realAddress = address + memoire->getBel();
	string varLoc = dep();
	memoire->setCell(realAddress, varLoc);
	cout << "Depilation et affectation de " << varLoc << " dans la variable local " << address << ".\n";
	memoire->incCo();
}

void Process::empg(int address)
{
	int realAddress = address + memoire->getBeg();
	string varGlo = memoire->getCell(realAddress);
	emp(varGlo);
	memoire->incCo();
}

void Process::depg(int address)
{
	int realAddress = address + memoire->getBeg();
	string varGlo = dep();
	memoire->setCell(realAddress, varGlo);
	cout << "Depilation et affectation de " << varGlo << " dans la variable globale " << address << ".\n";
	memoire->incCo();
}

void Process::empt(int address)
{
	int realAddress = address + memoire->getBeg();
	int i = stoi(dep());
	string value = memoire->getCell(realAddress + i);
	emp(value);
	memoire->incCo();
}

void Process::dept(int address)
{
	int realAddress = address + memoire->getBeg();
	string value = dep();
	int i = stoi(dep());
	memoire->setCell(realAddress + i, value);

}

void Process::addi()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "sp =" << memoire->getSp() << "and beg = " << memoire->getBeg();
		cout << "Cellules insuffisantes dans la pile pour effectuer l'addition !\n";
		stop();
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
		cout << t2 + t1 << ". ";
		emp(to_string(t2 + t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::sous()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la soustraction !\n";
		stop();
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
		cout << t2 - t1 << ". ";
		emp(to_string(t2 - t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::mul()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la multiplication !\n";
		stop();
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
		cout << t2 * t1 << ". ";
		emp(to_string(t2 * t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::div()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer la division !\n";
		stop();
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
		cout << t2 / t1 << ". ";
		emp(to_string(t2 / t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::mod()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour effectuer le modulo !\n";
		stop();
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
		cout << t2 % t1 << ". ";
		emp(to_string(t2 % t1));

		// Next instruction
		memoire->incCo();
	}
}

void Process::egal()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'egalite !\n";
		stop();
	}
	else {
		// Popping out first term
		string t1 = dep();

		// Popping out second term
		string t2 = dep();

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
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'inferiorité !\n";
		stop();
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t2 < t1) {
			cout << t2 << " < " << t1 << "\n";
			emp(to_string(1));
		}
		else {
			cout << t2 << " !< " << t1 << "\n";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::infeg()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'infeg !\n";
		stop();
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t2 <= t1) {
			cout << t2 << " <= " << t1 << "\n";
			emp(to_string(1));
		}
		else {
			cout << t2 << " !<= " << t1 << "\n";
			emp(to_string(0));
		}

		// Next instruction
		memoire->incCo();
	}
}

void Process::non()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier !\n";
		stop();
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (t1 == 0) {
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
	memoire->incCo();
}


void Process::dup()
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 1) {
		cout << "sp =" << memoire->getSp() << "and beg = " << memoire->getBeg();
		cout << "Cellules insuffisantes dans la pile pour effectuer la duplication !\n";
		stop();
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

void Process::stop()
{
	exit(0);
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
		stop();
	}
	else
	{
		memoire->setCell(memoire->getSp(), value);
		memoire->incSp();
		cout << "Empilement de " << value << " dans la cellule: " << memoire->getStCellNum(memoire->getSp()) << ".\n";
	}
}

string Process::ecriv()
{
	string value;
	if (memoire->stackEmpty()) {
		cout << "Pile vide !\n";
		return "";
	}
	else {
		// Popping out stack
		value = dep();

		// Writing to debug
		cout << value << ".\n";

		// Writing to console
		
	}

	// Next instruction
	memoire->incCo();

	return value;
}

void Process::saut(int address)
{
	memoire->setCo(address);
}

void Process::sivrai(int address)
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 1) {
		cout << "Cellules insuffisantes dans la pile pour verifier si vrai !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (t1) {
			saut(address);
		}
		else {
			memoire->incCo();
		}
	}
}

void Process::sifaux(int address)
{
	if (memoire->getSp() <= memoire->getBeg() + memoire->getVarGloNum() + 1) {
		cout << "Cellules insuffisantes dans la pile pour verifier si faux !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		if (!t1) {
			saut(address);
		}
		else {
			memoire->incCo();
		}
	}
}

void Process::appel(int address)
{
	emp(to_string(memoire->getCo() + 1));
	saut(address);
}

void Process::retour()
{
	int address;
	address = stoi(dep());
	saut(address);
	cout << "Retour effectue\n";
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
	memoire->setSp(memoire->getBel());
	memoire->setBel(stoi(dep()));

	// Next instruction
	memoire->incCo();
}

void Process::pile(int number)
{
	memoire->setSp(memoire->getSp() + number);
	cout << number << " cellules reservees dans la memoire\n";
	memoire->incCo();
}

