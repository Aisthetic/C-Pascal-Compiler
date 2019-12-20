#include "Interpreter.h"

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
}

void Interpreter::exInstr()
{
    int cursor = memoire->getCo();
    currentInstruction = memoire->getCell(cursor);
    
    // Recognition of the instruction
    if (currentInstruction == "STOP") {
        // what to do when stopped
    }
    else { // Not a stoppign instruction
        cout << currentInstruction << ": ";
		if (currentInstruction.substr(0, 4) == "EMPC") {
			process->empc(currentInstruction.substr(5));
        }
		/*else if (currentInstruction.substr(0, 4) == "EMPL") {
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
		else if (currentInstruction.substr(0, 4) == "DEPT") {
			process->dept(stoi(currentInstruction.substr(5)));
		}*/
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
            process->ecriv();
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
		/*else if (currentInstruction.substr(0, 4) == "PILE") {
			process->pile(stoi(currentInstruction.substr(5)));
		}*/
        else if (currentInstruction == "DUP") {
            process->dup();
        }
		else if (currentInstruction == "POP") {
			process->pop();
		}
        else {
            cout << "Instruction non reconnue !";
        }
        memoire->incCo(); // has to change since functions call doesnt increment co but changes it completely 
        exInstr();
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
