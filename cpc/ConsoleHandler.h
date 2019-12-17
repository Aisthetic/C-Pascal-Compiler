#pragma once
#include <string>
using namespace std;
class ConsoleHandler
{
public:
	static void logDebug(string caller, string message);
	static void logError(string caller, string message);
	static void resetColor();
	ConsoleHandler();
	~ConsoleHandler();
};

