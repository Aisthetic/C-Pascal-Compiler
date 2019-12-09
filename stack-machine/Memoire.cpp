#include "Memoire.h"

Memoire::Memoire(vector<string> code)
{
	// Copying code to its place on the memory
	std::copy(code.begin(), code.end(), cells.begin());

}

void Memoire::empc(int value)
{

}
