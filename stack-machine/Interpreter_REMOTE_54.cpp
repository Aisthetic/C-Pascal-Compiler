#include "Interpreter.h"

using namespace std;


void Interpreter::codeFile(string file)
{
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
            code.push_back(line);
        }
        input.close();
    }
}