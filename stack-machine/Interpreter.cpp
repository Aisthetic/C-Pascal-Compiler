#include "Interpreter.h"
#include "CLI11.hpp"

using namespace std;


//Constructeurs
Interpreter::Interpreter(string file)
{
    // Initializing code 
    codeFile(file);

    // Initialising memory with the code
    memoire = new Memoire(code);

    // Initialising process
    process = new Process(memoire);

	// Debug mode
	string answer;
	cout << "Lancer avec le mode debug (oui/yes) ? ";
	cin >> answer;
	if (answer.substr(0, 1) == "y" || answer.substr(0, 1) == "o") {
		debugMode = true;
		string test;
		getline(cin, test);
	}
	clearConsole();
}

void Interpreter::drawCell(int num, string value)
{
	cout << "|--|-------------------------|" << "\n";
	cout << "|";
	if (num < 10) { cout << "0" << num; }
	else { cout << num; }
	cout << "| ";
	cout << value;
	int remainingSpace = 24 - (int)value.length();
	cout << string(remainingSpace, ' ');
	cout << "|\n";
}

void Interpreter::endDrawing()
{
	cout << "|--|-------------------------|" << "\n";
}

void Interpreter::drawStack()
{
	int i = memoire->getSp() - 1;
	while (memoire->getStCellNum(i + 1) >= 0) {
		drawCell(memoire->getStCellNum(i + 1), memoire->getCell(i));
		i--;
	}
	endDrawing();
}

void Interpreter::drawPConsoleLine(int line)
{
	string value = console[line];
	int remainingSpace = 42 - (int)value.length();
	cout << "|" << value << string(remainingSpace, ' ') << "|\n";
}

void Interpreter::drawPConsole()
{
	cout << "\n\nConsole :\n";
	cout << "|------------------------------------------|\n";
	for (int i = 0; i < console.size(); i++) {
		drawPConsoleLine(i);
	}
	cout << "|------------------------------------------|\n\n";
}

void Interpreter::clearConsole()
{
	//cout << "\033[2J\033[1;1H";
	cout << string(100, '\n');
}

void Interpreter::exInstr()
{
    int cursor = memoire->getCo();
    currentInstruction = memoire->getCell(cursor);
    
    // Recognition of the instruction
    if (currentInstruction == "STOP") {
		cout << "STOP: Arret du programme.\n";
		drawPConsole();
		process->stop();
    }
	else if (currentInstruction.substr(0, 1) == "#") {
		memoire->incCo();
		exInstr();
	}
    else { // Not a stopping instruction

        cout << currentInstruction << ": ";
		if (currentInstruction.substr(0, 4) == "EMPC") {
			process->empc(currentInstruction.substr(5));
        }
		else if (currentInstruction.substr(0, 4) == "EMPL") {
			process->empl(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 4) == "DEPL") {
			process->depl(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 4) == "EMPG") {
			process->empg(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 4) == "DEPG") {
			process->depg(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 4) == "EMPT") {
			process->empt(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 4) == "DEPT") {
			process->dept(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction == "ADD") {
			process->addi();
		}
        else if (currentInstruction == "SOUS") {
            process->sous();
        }
		else if (currentInstruction == "MUL") {
			process->mul();
		}
		else if (currentInstruction == "DIV") {
			process->div();
		}
		else if (currentInstruction == "MOD") {
			process->mod();
		}
		else if (currentInstruction == "EGAL") {
			process->egal();
		}
		else if (currentInstruction == "INF") {
			process->inf();
		}
		else if (currentInstruction == "INFEG") {
			process->infeg();
		}
		else if (currentInstruction == "NON") {
			process->non();
		}
		else if (currentInstruction == "LIRE") {
			process->lire();
		}
        else if (currentInstruction == "ECRIV") {
            console.push_back(process->ecriv());
        }
		else if (currentInstruction.substr(0, 4) == "SAUT") {
			process->saut(stoi(currentInstruction.substr(5)));
		}
		else if (currentInstruction.substr(0, 6) == "SIVRAI") {
			process->sivrai(stoi(currentInstruction.substr(7)));
		}
		else if (currentInstruction.substr(0, 6) == "SIFAUX") {
			process->sifaux(stoi(currentInstruction.substr(7)));
		}
		else if (currentInstruction.substr(0, 5) == "APPEL") {
			process->appel(stoi(currentInstruction.substr(6)));
		}
		else if (currentInstruction == "RETOUR") {
			process->retour();
		}
		else if (currentInstruction == "ENTREE") {
			process->entree();
		}
		else if (currentInstruction == "SORTIE") {
			process->sortie();
		}
		else if (currentInstruction.substr(0, 4) == "PILE") {
			if (firstLine) {
				memoire->setVarGloNum(stoi(currentInstruction.substr(5)));
			}
			else {
				process->pile(stoi(currentInstruction.substr(5)));
			}
		}
        else if (currentInstruction == "DUP") {
            process->dup();
        }
		else if (currentInstruction == "POP") {
			process->pop();
		}
        else {
            cout << "Instruction non reconnue !";
        }
		if (debugMode) {
			cout << "\n\n";
			string test;
			drawStack();
			drawPConsole();
			cin.clear();
			getline(cin, test);
			clearConsole();
			if (firstLine) firstLine = false;
			exInstr();
		}
		else {
			if (firstLine) firstLine = false;
			exInstr();
		}
    }
}

void Interpreter::codeFile(string file)
{
    ifstream input;
    input.open(file);
    string line;

    if (!input.good()) {
        cout << "Erreur lors de l'ouverture du fichier " << file << endl;
        exit(1);
    }

    if (input.is_open()){
        while (!input.eof())
        {
            getline(input, line);
            code.push_back(line);// premiere ligne est code[0]==string ; TO-DO:changement de type 
        }
    }
    input.close();
}
