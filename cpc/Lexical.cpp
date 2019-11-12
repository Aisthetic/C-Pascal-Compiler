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
	unite.attribut = 0;

	while (estBlanc(currentChar))//sauter les blancs
		lireCar();

	switch (currentChar) {
	case ';':
		lireCar();
		unite.UL = PTVRG;
		break;
	case ',':
		lireCar();
		unite.UL = VIRG;
		break;
	case '{':
		lireCar();
		unite.UL = ACCOUV;
		break;
	case '}':
		lireCar();
		unite.UL = ACCFERM;
		break;
	case '(':
		lireCar();
		unite.UL = PAROUV;
		break;
	case ')':
		lireCar();
		unite.UL = PARFERM;
		break;
	case '[':
		lireCar();
		unite.UL = CROOUV;
		break;
	case ']':
		lireCar();
		unite.UL = CROFER;
		break;
	case '&':
		lireCar();
		unite.UL = ET;
		break;
	case '|':
		lireCar();
		unite.UL = OU;
		break;
	case '+':
		lireCar();
		unite.UL = ADD;
		break;
	case '-':
		lireCar();
		unite.UL = SOUS;
	case '*':
		lireCar();
		unite.UL = MUL;
		break;
	case '/':
		lireCar();
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
		lireCar();
		unite.UL = EGAL;
		break;
	case '!':
		lireCar();
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
			vector<int> lexeme;
			do {
				lexeme.push_back(currentChar - '0');
				lireCar();
			} while (estChiffre());
			reverse(lexeme.begin(), lexeme.end());
			int decimal = 1;
			int total = 0;
			for (auto& it : lexeme)
			{
				total += it * decimal;
				decimal *= 10;
			}
			unite.UL = CONST;
			unite.attribut = total;
		}
		else if (estCaractere())
		{
			vector<char> lexeme;

			do {
				lexeme.push_back(currentChar);
				lireCar();
			} while (estCaractere() || estChiffre());
			string str(lexeme.begin(), lexeme.end());
			if (motsReserves.existe(str)!=-1)
			{
				unite.UL = IDENT;
				unite.attribut = motsReserves.existe(str);
			}
			else
			{
				if (indetifs.existe(str) == -1)
				{
					indetifs.ajouter(str);
				}
				unite.attribut = indetifs.existe(str);
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
	return currentChar >= '0' && currentChar <= '9';
}

bool Lexical::estCaractere()
{
	return ((currentChar >= 'A' && currentChar <= 'Z') || (currentChar >= 'a' && currentChar <= 'z'));
}

bool Lexical::estBlanc(char c)
{
	if (c == '#')//commentaire
	{
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		lireCar();
	}
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
		output << "UL: " << unite.UL << ", Attribut: " << unite.attribut << endl;
	}
}

void Lexical::setInput(string file)
{
	input.open("main.txt");

	if (!input.good()) {
		cout << "Erreur lors de l'ouverture du fichier " << file << endl;
	}
}


