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
			wcout << L"Прочитанные сообщения:" << endl;
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
		wcout << L"Возникла ошибка при открытии файла (" << fileName << L")!\n"
			<< L"Возможные причины:\n"
			<< L"1. Данный файл отсутствует в папке с программой\n"
			<< L"2. У программы нет прав для того, чтобы отрыть данный файл\n"
			<< L"3. Произошла непредвиденная ошибка\n"
			<< L"Если проблема попадает под пункт 2 или 3, то необходимо сообщить разработчику" << endl;
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
			// поиск фразы "От"
			for (long long chN = 0; chN < messageBuffer.size() - 1; chN++)
			{
				if (messageBuffer[chN] == L'О' && messageBuffer[chN + 1] == L'т')
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
					wcout << L"[analyzeFileForStudentNicknames exception] Не удалось найти в сообщении " << i << L" фразу \"От\"!" << endl;
				}
			}
		}

		if (analyzerMode == 1)
		{
			expressionEndIndex = 8;
		}


		if (expressionEndIndex > 0)
		{

			// анализ строки сообщения
			for (long long chN = expressionEndIndex + 1; chN < messageBuffer.size(); chN++)
			{
				// получение ника студента
				if (static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'A') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'Z') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'a') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'z') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'А') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'Я') ||
					static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'а') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'я'))
				{
					studentNameBuffer.push_back(messageBuffer[chN]);
					isExpressionProcessing = true;
				}

				// получение номера группы
				if (static_cast<int>(messageBuffer[chN]) >= static_cast<int>(L'0') && static_cast<int>(messageBuffer[chN]) <= static_cast<int>(L'9'))
				{
					studentGroupBufferStr.push_back(messageBuffer[chN]);
				}

				// отделение имени от отчества пробелом
				if (isExpressionProcessing && messageBuffer[chN] == L' ')
				{
					studentNameBuffer.push_back(L' ');
					isExpressionProcessing = false;
				}

				// точка выхода
				if (chN < messageBuffer.size() - 2)
				{
					if (messageBuffer[chN] == L' ' && messageBuffer[chN + 1] == L':' && messageBuffer[chN + 2] == L' ')
						break;
				}

				// точка выхода
				if (chN < messageBuffer.size() - 1)
				{
					if (messageBuffer[chN] == L':' && messageBuffer[chN + 1] == L' ')
						break;
				}

				// точка выхода
				if (chN < messageBuffer.size() - 5)
				{
					if (messageBuffer[chN] == L' ' && messageBuffer[chN + 1] == L'к' && messageBuffer[chN + 2] == L'о' && messageBuffer[chN + 3] == L'м' && messageBuffer[chN + 4] == L'у' && messageBuffer[chN + 5] == L' ')
						break;
				}
			}

			// преобразование текстового номера группы в численный
			if (!studentGroupBufferStr.empty())
				studentGroupBuffer = stoi(studentGroupBufferStr);
			else
				studentGroupBuffer = 0;


			// сохранение ника и группы студента
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

		// сброс данных в временных пременных
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
		wcout << L"Ошибка отображения списков студентов: ни один студент не был обнаружен!" << endl;
		return;
	}

	while (true)
	{
		// вывод группы, студенты которой сейчас будут отображены
		if (currentGroup == 0)
			wcout << L"Неопознанные студенты:" << endl;
		else
			wcout << L"Студенты группы " << currentGroup << L':' << endl;

		// вывод студентов
		for (int i = 0; i < studentName.size(); i++)
		{
			if (studentGroup[i] == currentGroup)
				wcout << studentName[i] << endl;
			else
			{
				// регистрация новой группы, которая не была еще выведена
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

	// вывод общей информации о группах
	numberOfStudentsInTheGroup.resize(displayedGroups.size(), 0);
	for (int i = 0; i < displayedGroups.size(); i++)
	{
		// вывод группы, информация которой сейчас будет отображена
		if (displayedGroups[i] == 0)
			wcout << L"Количество неопознанных студентов: ";
		else
			wcout << L"Количество студентов группы " << displayedGroups[i] << L": ";

		// подсчет количества студентов данной группы
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