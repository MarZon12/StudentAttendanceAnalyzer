#include "FileAnalyzer.h"
FileAnalyzer::FileAnalyzer() {
	fileIsRead = false;
	fileAnalyzed = false;
	fileDisplayed = false;
	fileNameIsSet = false;
	analyzerMode = 0;

	displayStringsWhenReading = false;
}

FileAnalyzer::~FileAnalyzer() {}

///**********************************///
///             SETTERS              ///
///**********************************///

void FileAnalyzer::setFileName(wstring fileName) {
	this->fileName = fileName;
	fileNameIsSet = true;
}

void FileAnalyzer::setDisplayStringsWhenReading(bool value) {
	this->displayStringsWhenReading = value;
}

void FileAnalyzer::setAnalyzerMode(short mode) {
	this->analyzerMode = mode;
}

///**********************************///
///             GETTERS              ///
///**********************************///

wstring FileAnalyzer::getFileName() {
	return this->fileName;
}

bool FileAnalyzer::getDisplayStringsWhenReading() {
	return this->displayStringsWhenReading;
}

bool FileAnalyzer::getStateFileNameIsSet() {
	return this->fileNameIsSet;
}

bool FileAnalyzer::getStateFileIsRead() {
	return this->fileIsRead;
}

bool FileAnalyzer::getStateFileAnalyzed() {
	return this->fileAnalyzed;
}

bool FileAnalyzer::getStateFileDisplayed() {
	return this->fileDisplayed;
}

vector<wstring> FileAnalyzer::getMessageVector() {
	return this->message;
}

vector<wstring> FileAnalyzer::getStudentNameVector() {
	return this->studentName;
}

vector<int> FileAnalyzer::getStudentGroupVector() {
	return this->studentGroup;
}

///**********************************///
///           INSTRUMENTS            ///
///**********************************///

void FileAnalyzer::readFile() {
	fileIsRead = false;

	int counter = 0;
	wifstream fin;
	fin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	wstring messageBuffer;
	std::wstringstream wss;

	fin.open(fileName);
	if (fin.is_open())
	{
		if (displayStringsWhenReading)
			wcout << L"����������� ���������:" << endl;
		while (!fin.eof())
		{
			getline(fin, messageBuffer);

			if (!messageBuffer.empty())
			{
				if (displayStringsWhenReading)
				{
					counter++;
					wcout << L'[' << counter << L"]\t" << messageBuffer << endl;
				}
				message.push_back(messageBuffer);
			}
		}
		fin.close();
		fileIsRead = true;
	}
	else
	{
		wcout << L"�������� ������ ��� �������� ����� (" << fileName << L")!\n"
			<< L"��������� �������:\n"
			<< L"1. ������ ���� ����������� � ����� � ����������\n"
			<< L"2. � ��������� ��� ���� ��� ����, ����� ������ ������ ����\n"
			<< L"3. ��������� �������������� ������\n"
			<< L"���� �������� �������� ��� ����� 2 ��� 3, �� ���������� �������� ������������" << endl;
	}

}

void FileAnalyzer::analyzeFileForStudentNicknames() {
	fileAnalyzed = false;

	wstring messageBuffer;

	wstring studentNameBuffer;

	wstring studentGroupBufferStr;
	int studentGroupBuffer;

	bool studentIsAlreadyRegistered = false;

	bool isExpressionProcessing = false;

	long long expressionEndIndex = 0;
	for (int i = 0; i < message.size(); i++)
	{
		if (message[i].empty())
		{
			continue;
		}
		messageBuffer = message[i];

		if (analyzerMode == 0)
		{
			// ����� ����� "��"
			for (long long chN = 0; chN < messageBuffer.size() - 1; chN++)
			{
				if (messageBuffer[chN] == L'�' && messageBuffer[chN + 1] == L'�')
				{
					expressionEndIndex = chN + 1;
					break;
				}
				else
				{
					//wcout << L"[PNP]: " << messageBuffer[chN] << messageBuffer[chN + 1] << endl;
				}
				if (chN == messageBuffer.size() - 2)
				{
					wcout << L"[analyzeFileForStudentNicknames exception] �� ������� ����� � ��������� " << i << L" ����� \"��\"!" << endl;
				}
			}
		}

		if (analyzerMode == 1)
		{
			expressionEndIndex = 8;
		}


		if (expressionEndIndex > 0)
		{

			// ������ ������ ���������
			for (long long chN = expressionEndIndex + 1; chN < messageBuffer.size(); chN++)
			{
				// ��������� ���� ��������
				if (static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'A') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'Z') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'a') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'z') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'�') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'�') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'�') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'�'))
				{
					studentNameBuffer.push_back(messageBuffer[chN]);
					isExpressionProcessing = true;
				}

				// ��������� ������ ������
				if (static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'0') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'9'))
				{
					studentGroupBufferStr.push_back(messageBuffer[chN]);
				}

				// ��������� ����� �� �������� ��������
				if (isExpressionProcessing && messageBuffer[chN] == L' ')
				{
					studentNameBuffer.push_back(L' ');
					isExpressionProcessing = false;
				}

				// ����� ������
				if (chN < messageBuffer.size() - 2)
				{
					if (messageBuffer[chN] == L' ' && messageBuffer[chN + 1] == L':' && messageBuffer[chN + 2] == L' ')
						break;
				}

				// ����� ������
				if (chN < messageBuffer.size() - 1)
				{
					if (messageBuffer[chN] == L':' && messageBuffer[chN + 1] == L' ')
						break;
				}

				// ����� ������
				if (chN < messageBuffer.size() - 5)
				{
					if (messageBuffer[chN] == L' ' && messageBuffer[chN + 1] == L'�' && messageBuffer[chN + 2] == L'�' && messageBuffer[chN + 3] == L'�' && messageBuffer[chN + 4] == L'�' && messageBuffer[chN + 5] == L' ')
						break;
				}
			}

			// �������������� ���������� ������ ������ � ���������
			if (!studentGroupBufferStr.empty())
				studentGroupBuffer = stoi(studentGroupBufferStr);
			else
				studentGroupBuffer = 0;


			// ���������� ���� � ������ ��������
			if (studentName.size() == 0 && studentGroup.size() == 0)
			{
				studentName.push_back(studentNameBuffer);
				studentGroup.push_back(studentGroupBuffer);
			}
			else
			{
				for (int i = 0; i < studentName.size(); i++)
				{
					if (studentName[i] == studentNameBuffer && studentGroup[i] == studentGroupBuffer)
						studentIsAlreadyRegistered = true;
				}
				if (!studentIsAlreadyRegistered)
				{
					studentName.push_back(studentNameBuffer);
					studentGroup.push_back(studentGroupBuffer);
				}
			}

		}

		// ����� ������ � ��������� ���������
		messageBuffer.clear();
		studentNameBuffer.clear();
		studentGroupBufferStr.clear();
		studentGroupBuffer = 0;
		studentIsAlreadyRegistered = false;
		expressionEndIndex = 0;

	}

	fileAnalyzed = true;
}

void FileAnalyzer::coutDATA() {
	fileDisplayed = false;

	vector<int> displayedGroups;
	vector<int> numberOfStudentsInTheGroup;

	displayedGroups.push_back(0);
	int currentGroup = 0;

	int nextGroup = 0;
	bool nextGroupIsSet = false;

	bool isAmongTheDisplayedGroups = false;

	if (studentGroup.empty() || studentName.empty()) {
		wcout << L"������ ����������� ������� ���������: �� ���� ������� �� ��� ���������!" << endl;
		return;
	}

	while (true)
	{
		// ����� ������, �������� ������� ������ ����� ����������
		if (currentGroup == 0)
			wcout << L"������������ ��������:" << endl;
		else
			wcout << L"�������� ������ " << currentGroup << L':' << endl;

		// ����� ���������
		for (int i = 0; i < studentName.size(); i++)
		{
			if (studentGroup[i] == currentGroup)
				wcout << studentName[i] << endl;
			else
			{
				// ����������� ����� ������, ������� �� ���� ��� ��������
				if (!nextGroupIsSet)
				{
					for (int j = 0; j < displayedGroups.size(); j++)
					{
						if (studentGroup[i] == displayedGroups[j])
							isAmongTheDisplayedGroups = true;
					}
					if (!isAmongTheDisplayedGroups)
					{
						nextGroup = studentGroup[i];
						nextGroupIsSet = true;
						displayedGroups.push_back(nextGroup);
					}
					isAmongTheDisplayedGroups = false;
				}
			}
		}
		wcout << endl;

		if (nextGroupIsSet) {
			nextGroupIsSet = false;
			currentGroup = nextGroup;
		}
		else
			break;
	}

	// ����� ����� ���������� � �������
	numberOfStudentsInTheGroup.resize(displayedGroups.size(), 0);
	for (int i = 0; i < displayedGroups.size(); i++)
	{
		// ����� ������, ���������� ������� ������ ����� ����������
		if (displayedGroups[i] == 0)
			wcout << L"���������� ������������ ���������: ";
		else
			wcout << L"���������� ��������� ������ " << displayedGroups[i] << L": ";

		// ������� ���������� ��������� ������ ������
		for (int j = 0; j < studentGroup.size(); j++)
		{
			if (displayedGroups[i] == studentGroup[j])
			{
				numberOfStudentsInTheGroup[i]++;
			}
		}
		wcout << numberOfStudentsInTheGroup[i] << endl;
	}

	fileDisplayed = true;
}

void FileAnalyzer::clearStudentData() {
	message.clear();
	studentName.clear();
	studentGroup.clear();
}