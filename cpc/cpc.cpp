// cpc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "CLI11.hpp"
#include "Lexical.h"
#include "Syntaxique.h"
#include <unordered_map>
using namespace std;

int main(int argc, char* argv[])
{
	CLI::App app{ "Compilateur du language C-Pascal" };
	//Processing multiple files
	vector<string> files;
	app.add_option("files", files, "Files to add");

	CLI11_PARSE(app, argc, argv);

	//Utilisation du 2eme constructeur pour avoir acces au lexical depuis le main (facile à debug)
	Lexical *lexical = new Lexical();
	Syntaxique* syntaxique = new Syntaxique(lexical);

	for (auto file : files) {
		cout << "Processing file : " << file << endl;
		lexical->setInput(file,true,true);
		lexical->setupOutput();//pour créer un fichier d'output
		syntaxique->startParsing();
		cout << "Syntaxic done for " << file;
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
