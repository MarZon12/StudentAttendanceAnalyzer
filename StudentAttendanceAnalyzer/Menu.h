#pragma once
#include <string>
#include <iostream>

#include "FileAnalyzer.h"

using std::wstring;

using std::wcout;
using std::wcin;
using std::endl;
using std::getline;

class Menu
{
public:
	Menu();
	~Menu();

	void openMainMenu();

	void openFileAnalyzeMenu();


private:
	int version;

	FileAnalyzer FileAnalyzerObj;

	int getIntChoice();

	void clearCin();

	bool performTheActionAgain(wstring message);
};

