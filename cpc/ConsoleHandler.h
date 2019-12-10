#pragma once
#include <string>
using namespace std;
class ConsoleHandler
{
public:
	static void logDebug(string message);
	static void logError(string message);
	static void resetColor();
	ConsoleHandler();
	~ConsoleHandler();
};

