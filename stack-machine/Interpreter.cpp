#include "Interpreter.h"

using namespace std;


//Constructeurs
Interpreter::Interpreter()
{
    ;
}

void Intrepreter::exnextInstr() 
{
    return code[1]; int myNr = std::stoi(myString);
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