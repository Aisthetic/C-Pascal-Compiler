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
	else {
		memoire->setCell(memoire->getSp(), value);
		memoire->incSp();
		cout << "Empilement de " << value << ".\n";
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
		empc(to_string(t1 + t2));

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
		empc(to_string(t2 - t1));

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
		empc(to_string(t2 * t1));

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
		empc(to_string(t2 / t1));

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
		empc(to_string(t2 % t1));
	}
}

void Process::egal()
{
	if (memoire->getSp() <= memoire->getBeg() + 2) {
		cout << "Cellules insuffisantes dans la pile pour verifier l'égalité !\n";
	}
	else {
		// Popping out first term
		int t1 = stoi(dep());

		// Popping out second term
		int t2 = stoi(dep());

		if (t1 == t2) {
			cout << t1 << " == " << t2 << "\n";
			empc(to_string(1));
		}
		else {
			cout << t1 << " != " << t2 << "\n";
			empc(to_string(0));
		}
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
			empc(to_string(1));
		}
		else {
			cout << t1 << " !< " << t2 << "\n";
			empc(to_string(0));
		}
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
			empc(to_string(1));
		}
		else {
			cout << t1 << " !<= " << t2 << "\n";
			empc(to_string(0));
		}
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
			empc(to_string(1));
		}
		else {
			cout << t1 << " != 0\n.";
			empc(to_string(0));
		}
	}
}


void Process::dup()
{
	if (memoire->getSp() <= memoire->getBeg() + 1) {
		cout << "sp =" << memoire->getSp() << "and beg = " << memoire->getBeg();
		cout << "Cellules insuffisantes dans la pile pour effectuer la duplication !\n";
	}
	else {
		// Popping out stack
		string value = dep();

		// Stacking twice
		empc(value);
		empc(value);
	}
}

string Process::dep()
{
	return memoire->getCell(memoire->getSp() - 1);
	memoire->decSp();
}

void Process::ecriv()
{
	if (memoire->stackEmpty()) {
		cout << "Pile vide !";
	}
	else {
		// Popping out stack
		string value = dep();

		// Writing to console
		cout << value << ".\n";

		// Stacking the value again
		empc(value);
	}
}

