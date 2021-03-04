#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <sstream>

#include <codecvt>
#include <locale>

using std::wstring;
using std::wifstream;
using std::vector;

using std::wcout;
using std::endl;
using std::getline;


class FileAnalyzer
{
public:
	FileAnalyzer();
	~FileAnalyzer();

	///**********************************///
	///             SETTERS              ///
	///**********************************///
	
	void setFileName(wstring fileName);

	void setDisplayStringsWhenReading(bool value);
	
	void setAnalyzerMode(short mode);

	///**********************************///
	///             GETTERS              ///
	///**********************************///

	wstring getFileName();

	bool getDisplayStringsWhenReading();
	
	bool getStateFileNameIsSet();

	bool getStateFileIsRead();

	bool getStateFileAnalyzed();

	bool getStateFileDisplayed();

	vector<wstring> getMessageVector();

	vector<wstring> getStudentNameVector();

	vector<int> getStudentGroupVector();

	///**********************************///
	///           INSTRUMENTS            ///
	///**********************************///

	void readFile();

	void analyzeFileForStudentNicknames();

	void coutDATA();

	void clearStudentData();

private:
	wstring fileName;

	vector<wstring> message;

	vector<wstring> studentName;
	vector<int> studentGroup;

	//States
	bool fileNameIsSet;
	bool fileIsRead;
	bool fileAnalyzed;
	bool fileDisplayed;
	unsigned short analyzerMode;

	//Settings
	bool displayStringsWhenReading;
};