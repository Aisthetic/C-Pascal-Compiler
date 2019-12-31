#include "Interpreter.h"
<<<<<<< HEAD
=======

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
>>>>>>> 82d212ba7d233d22a8a3702204f9ea4c3af04688
