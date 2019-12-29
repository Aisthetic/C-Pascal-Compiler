#include "Lexical.h"
#include <vector>
#include <iterator>
#include "Hashage.h"
#include "Constants.h"
#include "ConsoleHandler.h"

using namespace std;

Lexical::Lexical(bool debug):lexicalTable('-', '|', '+')
{
	//Initializing members
	lexicalTable.add("Unite lexicale");
	lexicalTable.add("Lexeme");
	lexicalTable.add("Attribut");
	lexicalTable.endOfRow();
	currentChar = '$';
	initierMotsReserves();
	enableDebug = false;
	line = 1; col = 0;
	//Debugging
	logDebug("Lexical debugging is enabled");
}

Lexical::Lexical(string file, bool debug = false, bool logTableIdentifs = false, bool logTableMotsRes = false)
{
	currentChar = '$';
	if (enableDebug) {
		cout << ("Lexical debugging is enabled") << endl;
	}
	initierMotsReserves();
	setInput(file,logTableIdentifs,logTableMotsRes);
	enableDebug = debug;
	line = 1; col = 0;
}

Lexical::~Lexical()
{
	output.flush();
}

TUniteLexicale Lexical::uniteSuivante()
{
	TUniteLexicale unite;
	unite.UL = ERR;//Default case is always an error
	unite.attribut = 0;

	while (estBlanc(currentChar))
	{
		if (input.eof())//Reached end of file
		{
			currentChar = '$';
			lexicalTable.setAlignment(2, TextTable::Alignment::RIGHT);
			output<<lexicalTable;
			identifOutput << identifiants.afficher();
			motsResOutput << motsReserves.afficher();
			

		}
		else
			lireCar();
	}
	if (currentChar == '$')//in du traitement du fichier 
	{
		unite.UL = END;
		return unite;
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
		break;
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
		unite.UL = CONSTCAR;
		unite.attribut = currentChar;//code ascii
		lireCar();

		while (currentChar != '\'' || currentChar == '\n')//exemple d'erreur 'abc', fin de caractère = fin de ligne ou un autre "'"
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

			//*****collecting all the lexeme inside a vector*****

			do {
				lexeme.push_back(currentChar);
				lireCar();
			} while ((estCaractere() || estChiffre()));
			string str(lexeme.begin(), lexeme.end());

			//*****end of collection*****


			//starts figuring reserved words
			if (!str.compare("ecrire") || !str.compare("lire") || !str.compare("entier") || !str.compare("car") || !str.compare("retour") || !str.compare("si") || !str.compare("sinon") || !str.compare("alors") || !str.compare("tantque") || !str.compare("faire") || !str.compare("main"))
			{
				if (!str.compare("entier"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = ENTIER;
				}
				if (!str.compare("car"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = CAR;
				}
				if (!str.compare("si"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = SI;
				}
				if (!str.compare("sinon"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = SINON;
				}
				if (!str.compare("alors"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = ALORS;
				}
				if (!str.compare("tantque"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = TANTQUE;
				}
				if (!str.compare("faire"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = FAIRE;
				}
				if (!str.compare("retour"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = RETOUR;
				}
				if (!str.compare("main"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = MAIN;
				}
				if (!str.compare("ecrire"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = ECRIRE;
				}
				if (!str.compare("lire"))
				{
					unite.attribut = motsReserves.existe(str);
					unite.UL = LIRE;
				}
			}
			else if (motsReserves.existe(str) != -1)
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
	printLexicalUnits(unite);
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
	if (!input.eof()) {
		auto result = (bool)(input >> ::noskipws >> currentChar);
		col++;//incrementing number of columns as we just read a caracter
		logDebug("Current caracter "  + (currentChar == '\n' ? "EndOfLine": string(1,currentChar)) + " at Ln " + to_string(line) + ",Col " + to_string(col));//to print ↓ instead of nothing
		if (currentChar == '\n') {
			line++;
			col = 0;
		}
		return result;
	}
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
	motsReserves.ajouter("car");
	motsReserves.ajouter("main");
	motsReserves.ajouter("ecrire");
	motsReserves.ajouter("lire");
}

string Lexical::lexemeToString(TUniteLexicale unite)//pour afficher les lexemes
{
	switch (unite.UL)
	{
	case IDENT:
		//return identifiants.get(unite.attribut);
		return "identifiant";
		break;
	case CONST:
		return to_string(unite.attribut);
		break;
	case MOTCLE:
		return motsReserves.get(unite.attribut);
		break;

	case ENTIER:
		return "entier";
		break;
	case LIRE:
		return "lire";
		break;
	case ECRIRE:
		return "ecrire";
		break;
	case CAR:
		return "CAR";
		break;
	case SI:
		return "SI";
		break;
	case SINON:
		return "SINON";
		break;
	case ALORS:
		return "ALORS";
		break;
	case TANTQUE:
		return "TANTQUE";
		break;
	case FAIRE:
		return "FAIRE";
		break;
	case RETOUR:
		return "RETOUR";
		break;
	case MAIN:
		return "MAIN";
		break;
	case PTVRG:
		return ";";
		break;
	case VIRG:
		return ",";
		break;
	case ACCOUV:
		return "{";
		break;
	case ACCFERM:
		return "}";
		break;
	case PAROUV:
		return "(";
		break;
	case PARFERM:
		return ")";
		break;
	case CROOUV:
		return "[";
		break;
	case CROFER:
		return "]";
		break;
	case ET:
		return "&";
		break;
	case OU:
		return "|";
		break;
	case ADD:
		return "+";
		break;
	case SOUS:
		return "-";
		break;
	case MUL:
		return "*";
		break;
	case DIV:
		return "/";
		break;
	case INFEGAL:
		return "<=";
		break;
	case INF:
		return "<";
		break;
	case EGAL:
		return "=";
		break;
	case NONEGAL:
		return "!=";
		break;
	case NON:
		return "!";
		break;
	case SUPEGAL:
		return ">=";
		break;
	case SUP:
		return ">";
		break;
	case ERR:
		return "ERR";
		break;
	default:
		break;
	}
}

void Lexical::processAllFile()
{
	setupOutput();
	while (!input.eof()) {
		TUniteLexicale unite = uniteSuivante();
		output << endl << "UL: " << unite.UL << ", Attribut: " << unite.attribut;
		lexemeToString(unite);//TODO: review this warning as a team
	}
}
void Lexical::printLexicalUnits(TUniteLexicale unite)
{
	lexicalTable.add(to_string(unite.UL));
	lexicalTable.add(lexemeToString(unite));
	lexicalTable.add(to_string(unite.attribut));
	lexicalTable.endOfRow();
}
void Lexical::setInput(string file, bool logTableIdentifs = false, bool logTableMotsRes = false)
{
	inputFilename = file;
	input.open(file);
	if (!input.good()) {
		logError("Erreur lors de l'ouverture du fichier " + file);
	}
	if (logTableIdentifs) {
		cout << ("Identificators table will be logged at " + TABLE_IDENTIF_OUTPUT_DIRECTORY) << endl;
		setupIdentifsOutput();
	}
	if (logTableMotsRes) {
		setupMotsResOutput();
		cout << ("Reserved words table will be logged at " + TABLE_MOTS_RES_OUTPUT_DIRECTORY) << endl;
	}
	lireCar();
}

string Lexical::getInputFileNameWithoutExt()
{
	size_t lastindex = inputFilename.find_last_of(".");
	return inputFilename.substr(0, lastindex);
}


//Cree un fichier d'output 
void Lexical::setupOutput() {
	if (!output.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		output.open(LEXICAL_OUTPUT_DIRECTORY + "/" + getInputFileNameWithoutExt() + ".lex");
		if (!output.is_open()) {
			logError("Impossible d'ouvrir le fichier d'output");
			return;
		}
	}
}

void Lexical::setupIdentifsOutput()
{
	if (!identifOutput.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		auto dir = TABLE_IDENTIF_OUTPUT_DIRECTORY + "/" + getInputFileNameWithoutExt() + ".ident";
		identifOutput.open(dir);
		if (!identifOutput.is_open()) {
			logError("Impossible d'ouvrir le fichier d'output de la table des identifs");
			return;
		}
	}
}

void Lexical::setupMotsResOutput()
{
	if (!motsResOutput.is_open())//si un input est déjà ouvert on passe au processing direct
	{
		motsResOutput.open(TABLE_MOTS_RES_OUTPUT_DIRECTORY + "/" + getInputFileNameWithoutExt() + ".mrs");
		if (!motsResOutput.is_open()) {
			logError("Impossible d'ouvrir le fichier d'output de la table des mots réservés");
			return;
		}
	}
}

int Lexical::getLine()
{
	return line;
}

int Lexical::getColumn()
{
	return col;
}


void Lexical::logDebug(string message)
{
	if (enableDebug)
		ConsoleHandler:: logDebug("Lexical" , message);
}

void Lexical::logError(string error)
{
	ConsoleHandler::logDebug("Lexical" , error);
}
