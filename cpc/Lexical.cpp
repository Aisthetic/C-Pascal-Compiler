#include "Lexical.h"
#include <vector>
#include <iterator>
#include "Hashage.h"
#include "Constants.h"
using namespace std;


Lexical::Lexical()
{
	currentChar = '$';
	initierMotsReserves();
}

Lexical::~Lexical()
{
	//todo
}

TUniteLexicale Lexical::uniteSuivante()
{

	TUniteLexicale unite;
	unite.UL = ERR;//Default case is always an error
	unite.attribut = 0;

	if (currentChar=='$')//in du traitement du fichier 
	{
		unite.UL = END;
		return unite;
	}
	while (estBlanc(currentChar) && lireCar())
	{
		//silence is golden	
	}
	//Déclaration utilisée dans le switch
	bool err = false;//case '\''
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
	case '\''://Constante caractère
		lireCar();//On lit le contenu de la constante
		unite.UL = CAR;
		unite.attribut = currentChar;//code ascii
		lireCar();
		
		while (currentChar != '\'' || currentChar == '\n')//exemple d'erreur 'abc', fin de ligne = fin de caractère
		{
			err = true;
			input.ignore();
		}
		if (err) {
		unite.UL = ERR;
		unite.attribut = 1;//Caractère incorrect
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
			vector<int> lexeme{};
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
			vector<char> lexeme{};

			do {
				lexeme.push_back(currentChar);
				lireCar();
			} while ((estCaractere() || estChiffre()));
			string str(lexeme.begin(), lexeme.end());
			if (motsReserves.existe(str) != -1)
			{
				unite.UL = MOTCLE;
				unite.attribut = motsReserves.existe(str);
			}
			else
			{
				if (identifiants.existe(str) == -1)
				{
					identifiants.ajouter(str);
				}
				unite.attribut = identifiants.existe(str);
				unite.UL = IDENT;
			}
		}
		else
			unite.attribut = 0;//erreur: charactere non reconnu

	}
	if (input.eof())
		currentChar = '$';//so that next uniteSuivante's call returns an UL.end
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
	if (c == '#')//on saute les commentaires
	{
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		lireCar();
	}
	return (c == ' ') || (c == '\t') || (c == '\n') || (c == '\v');
}

bool Lexical::lireCar()
{
	if (!input.is_open())//si l'input stream est ouvert
		return false;
	if(logDebug)
		cout << "Current car : " << currentChar << endl;
	if (!input.eof())//reached end of line
		return (bool)(input >> ::noskipws >> currentChar);
	return false;

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

void Lexical::lexemeToString(TUniteLexicale unite)//pour afficher les lexemes
{
	if (!logDebug)
		return;
	switch (unite.UL)
	{
	case 23:
		output << "\t lexeme: " << identifiants.pop(unite.attribut);
		break;
	case 21:
		output << "\t lexeme: " << unite.attribut;
		break;
	case 22:
		output << "\t lexeme: " << motsReserves.pop(unite.attribut);
		break;
	case 0:
		output << "\t lexeme: " << ";";
		break;
	case 1:
		output << "\t lexeme: " << ",";
		break;
	case 2:
		output << "\t lexeme: " << "{";
		break;
	case 3:
		output << "\t lexeme: " << "}";
		break;
	case 4:
		output << "\t lexeme: " << "(";
		break;
	case 5:
		output << "\t lexeme: " << ")";
		break;
	case 6:
		output << "\t lexeme: " << "[";
		break;
	case 7:
		output << "\t lexeme: " << "]";
		break;
	case 8:
		output << "\t lexeme: " << "&";
		break;
	case 9:
		output << "\t lexeme: " << "|";
		break;
	case 10:
		output << "\t lexeme: " << "+";
		break;
	case 11:
		output << "\t lexeme: " << "-";
		break;
	case 12:
		output << "\t lexeme: " << "*";
		break;
	case 13:
		output << "\t lexeme: " << "/";
		break;
	case 14:
		output << "\t lexeme: " << "<=";
		break;
	case 15:
		output << "\t lexeme: " << "<";
		break;
	case 16:
		output << "\t lexeme: " << "=";
		break;
	case 17:
		output << "\t lexeme: " << "!=";
		break;
	case 18:
		output << "\t lexeme: " << "!";
		break;
	case 19:
		output << "\t lexeme: " << ">=";
		break;
	case 20:
		output << "\t lexeme: " << ">";
		break;
	case 24:
		output << "\t lexeme: " << "ERR";
		break;
	default:
		break;
	}
}


void Lexical::processAllFile()
{
	if (!output.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		output.open(LEXICAL_OUTPUT_DIRECTORY + "/" + inputFilename);
		if (!output.is_open()) {
			cout << "Impossible d'ouvrir le fichier d'output";
			return;
		}
	}
	while (!input.eof()) {
		auto unite = uniteSuivante();
		output << endl << "UL: " << unite.UL << ", Attribut: " << unite.attribut << ", Lexeme: " << unite.attribut;
	}
	//pour des soucis de débuggage : 
	identifiants.afficher();
	motsReserves.afficher();
}

void Lexical::setInput(string file)
{
	inputFilename = file;
	input.open(file);
	if (!input.good()) {
		cout << "Erreur lors de l'ouverture du fichier " << file << endl;
	}
	lireCar();
}


