#include "Lexical.h"
#include <vector>
#include <iterator>
#include "Hashage.h"
using namespace std;


Lexical::Lexical()
{
	initierMotsReserves();
}

Lexical::~Lexical()
{

}

TUniteLexicale Lexical::uniteSuivante()
{
	TUniteLexicale unite;
	unite.UL = ERR;//Default case is always an error

	while (estBlanc(currentChar))//sauter les blancs
		lireCar();

	switch (currentChar) {
	case ';':
		unite.UL = PTVRG;
		break;
	case ',':
		unite.UL = VIRG;
		break;
	case '{':
		unite.UL = ACCOUV;
		break;
	case '}':
		unite.UL = ACCFERM;
		break;
	case '(':
		unite.UL = PAROUV;
		break;
	case ')':
		unite.UL = PARFERM;
		break;
	case '[':
		unite.UL = CROOUV;
		break;
	case ']':
		unite.UL = CROFER;
		break;
	case '&':
		unite.UL = ET;
		break;
	case '|':
		unite.UL = OU;
		break;
	case '+':
		unite.UL = ADD;
		break;
	case '-':
		unite.UL = SOUS;
	case '*':
		unite.UL = MUL;
		break;
	case '/':
		unite.UL = DIV;
		break;
	case '<':
		lireCar();
		if (currentChar == '=')
		{
			unite.UL = INFEGAL;
		}
		else
		{
			unite.UL = INF;
		}
		break;
	case '=':
		unite.UL = EGAL;
		break;
	case '!':
		unite.UL = NON;
		break;
	case '>':
		lireCar();
		if (currentChar == '=')
		{
			unite.UL = SUPEGAL;
		}
		else
		{
			unite.UL = SUP;
		}
		break;
	default:
		if (estChiffre())
		{
			vector<char> lexeme;
			do{
				lireCar();
				lexeme.push_back(currentChar);
			}
			while(estChiffre());
			reverse(lexeme.begin(), lexeme.end());
			int decimal = 1;
			int total = 0;
			for (auto& it : lexeme)
			{
				total += it * decimal;
				decimal *= 10;
			}
			unite.UL = CONST;
			unite.attribut=total;
		}
		else if (estCaractere())
		{
			vector<char> lexeme;
			
			do{
				lireCar();
				lexeme.push_back(currentChar);
			}
			while(estCaractere()||estChiffre());
			string str(lexeme.begin(), lexeme.end());
			if(motsReserves.existe(str))
			{
				unite.UL = IDENT;				
			}
			else
			{
				if(indetifs.existe(str)==-1)
				{
					indetifs.ajouter(str);
				}
				unite.attribut= motsReserves.existe(str);
				unite.UL = MOTCLE;
			}
		}
		else
			unite.attribut = 0;//erreur: charactere non reconnu

	}
	return unite;
}

bool Lexical::estChiffre()
{
	return (currentChar >= 0 && currentChar <= 9);
}

bool Lexical::estCaractere()
{
	return ((currentChar>='A'&&currentChar<='Z')||(currentChar>='a'&&currentChar<='z'));
}

bool Lexical::estBlanc(char c)
{
	return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\v');
}

bool Lexical::lireCar()
{
	if (!input.is_open()) 
		return false;
	cout << "Current car : " << currentChar << endl;
 	return (bool)(input >> currentChar);
}

void Lexical::initierMotsReserves()
{
	motsReserves.ajouter("entier");
	motsReserves.ajouter("si");
	motsReserves.ajouter("alors");
	motsReserves.ajouter("sinon");
	motsReserves.ajouter("tantque");
	motsReserves.ajouter("faire");
	motsReserves.ajouter("retour");
	motsReserves.ajouter("ecrire");
	motsReserves.ajouter("lire");
	motsReserves.ajouter("Car");
	motsReserves.ajouter("main");
}

void Lexical::processAllFile()
{
	if (!lireCar()) {
		return;
	}
	if (!output.is_open())
		output.open("./lexicalOutput.txt");
	while (!input.eof()) {
		auto unite = uniteSuivante();
		cout << unite.UL << endl;
	}
}

void Lexical::setInput(string file)
{
	input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		input.open("main.txt");
	}
	catch (exception e) {
		cout << "Erreur lors de l'ouverture du fichier " << file << endl;
	}
}


