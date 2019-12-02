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
		if (estChiffre()) //dans le cas d'un chiffre
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
		else if (estCaractere())//dans le cas d'une suite de alphabets
		{
			vector<char> lexeme{};

			do {
				lexeme.push_back(currentChar);
				lireCar();
			} while ((estCaractere() || estChiffre()));
			string str(lexeme.begin(), lexeme.end());
			//////////////////////////////////////////////////////////////////
			if (!str.compare("entier") || !str.compare("car"))
			{
				if (!str.compare("entier"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = ENTIER;
					unite.attribut = motsReserves.existe(str);
				}
				if (!str.compare("car"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = CAR;
					unite.attribut = motsReserves.existe(str);
				}
			}
			else if(motsReserves.existe(str) != -1)
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
	motsReserves.ajouter("car");
	motsReserves.ajouter("main");
}

void Lexical::lexemeToString(TUniteLexicale unite)//pour afficher les lexemes
{
	if (!logDebug)
		return;
	switch (unite.UL)
	{
	case IDENT:
		output << "\t lexeme: " << identifiants.pop(unite.attribut);
		break;
	case CONST:
		output << "\t lexeme: " << unite.attribut;
		break;
	case MOTCLE:
		output << "\t lexeme: " << motsReserves.pop(unite.attribut);
		break;
	case PTVRG:
		output << "\t lexeme: " << ";";
		break;
	case VIRG:
		output << "\t lexeme: " << ",";
		break;
	case ACCOUV:
		output << "\t lexeme: " << "{";
		break;
	case ACCFERM:
		output << "\t lexeme: " << "}";
		break;
	case PAROUV:
		output << "\t lexeme: " << "(";
		break;
	case PARFERM:
		output << "\t lexeme: " << ")";
		break;
	case CROOUV:
		output << "\t lexeme: " << "[";
		break;
	case CROFER:
		output << "\t lexeme: " << "]";
		break;
	case ET:
		output << "\t lexeme: " << "&";
		break;
	case OU:
		output << "\t lexeme: " << "|";
		break;
	case ADD:
		output << "\t lexeme: " << "+";
		break;
	case SOUS:
		output << "\t lexeme: " << "-";
		break;
	case MUL:
		output << "\t lexeme: " << "*";
		break;
	case DIV:
		output << "\t lexeme: " << "/";
		break;
	case INFEGAL:
		output << "\t lexeme: " << "<=";
		break;
	case INF:
		output << "\t lexeme: " << "<";
		break;
	case EGAL:
		output << "\t lexeme: " << "=";
		break;
	case NONEGAL:
		output << "\t lexeme: " << "!=";
		break;
	case NON:
		output << "\t lexeme: " << "!";
		break;
	case SUPEGAL:
		output << "\t lexeme: " << ">=";
		break;
	case SUP:
		output << "\t lexeme: " << ">";
		break;
	case ERR:
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
		output << endl << "UL: " << unite.UL << ", Attribut: " << unite.attribut;
		lexemeToString(unite);
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


