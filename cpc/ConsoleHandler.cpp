#include "ConsoleHandler.h"
#include "conio.h"
#include <iostream>
#include <windows.h>
using namespace std;
//ref http://www.cplusplus.com/forum/beginner/54360/
/*
The different color codes are

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/
void ConsoleHandler::logDebug(string caller,string message)
{
	if (message == "\n")
		return;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	/*
	 * First save the current color information
	 */
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	 * Set the new color information
	 */
	SetConsoleTextAttribute(h, 10);

	cout << "[" << caller << "]" << message << endl;

	/*
	 * Restore the original colors
	 */
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void ConsoleHandler::logError(string caller, string message)
{
	if (message == "\n" || message == "")
		return;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	/*
	 * First save the current color information
	 */
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	/*
	 * Set the new color information
	 */
	SetConsoleTextAttribute(h, 12);

	cout << "[" << caller  << "]" << message << endl;

	/*
	 * Restore the original colors
	 */
	SetConsoleTextAttribute(h, wOldColorAttrs);
}

void ConsoleHandler::resetColor()
{
}

ConsoleHandler::ConsoleHandler()
{
}


ConsoleHandler::~ConsoleHandler()
{
}
