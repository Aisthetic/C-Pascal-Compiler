#include "Interpreter.h"

using namespace std;


//Constructeurs
Interpreter::Interpreter(string file)
{
    // Initializing code 
    codeFile(file);

    // Initialising memory with the code
    memoire = new Memoire(code);
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
        if (currentInstruction == "ADD") {
            memoire->addi();
        } // Substraction
        else if (currentInstruction == "SOUS") {
            memoire->sous();
        } // Stacking constant
        else if (currentInstruction.substr(0, 4) == "EMPC") { // TO-DO: check if generated code is absolutely correct
            memoire->empc(currentInstruction.substr(5));
        } // Writing to console
        else if (currentInstruction == "ECRIV") {
            memoire->ecriv();
        } // Duplicate
        else if (currentInstruction == "DUP") {
            memoire->dup();
        }
        else {
            cout << "Instructions non reconnue !";
        }
        memoire->incCo(); // has to change since function call doesnt increment co but changes it completely
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
