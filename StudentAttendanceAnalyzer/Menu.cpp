#include "Menu.h"

Menu::Menu() { version = 2; }
Menu::~Menu() {}

void Menu::openMainMenu() {
	int choice;


	while (true)
	{
		wcout << L"StudentAttendanceAnalyzer V" << version << " by MarZon\n" << endl;

		wcout << L"[Главное меню]\n\n";
		wcout << L"Выберите интересующий пункт:\n"
			<< L"1 - Проанализировать файл\n"
			<< L"2 - Отобразить предыдущий результат анализа файла\n"
			//<< L"Занести данные в базу (ЕЩЕ НЕ РЕАЛИЗОВАНО)" 
			<< L"Любая другая цифра - выйти из программы"
			<< endl;

		choice = this->getIntChoice();
		system("cls");
		switch (choice)
		{
		case 1:
			this->openFileAnalyzeMenu();
			break;

		case 2:
			if (FileAnalyzerObj.getStateFileAnalyzed())
			{
				this->FileAnalyzerObj.coutDATA();
			}
			else
				wcout << L"[Сообщение] Вы еще не анализировали файл!" << endl;

			break;

		/*
		case 3:
			this->openFileAnalyzeMenu();
			break;
		*/

		default:
			return;
			break;
		}
	}
}

void Menu::openFileAnalyzeMenu() {
	int choice;


	while (true)
	{
		wcout << L"StudentAttendanceAnalyzer V" << version << " by MarZon\n" << endl;

		wcout << L"[Меню анализатора файла]\n\n";
		wcout << L"Выберите формат данных:\n"
			<< L"1 - Вариант 1\n"
			<< L"2 - Вариант 2\n"
			<< L"Любая другая цифра - вернуться назад"
			<< endl;

		wcout << endl;
		wcout << L"Описание вариантов:\n"
			<< L"Вариант 1:\n"
			<< L"ЧЧ:ММ:СС	 От  НикСтудента : сообщение студента\n"
			<< L"ЧЧ:ММ:СС	 От  НикСтудента  кому  НикСтудента(Частное) : сообщение студента\n"
			<< L"Вариант 2:\n"
			<< L"ЧЧ:ММ:СС	НикСтудента:	сообщение студента"
			<< endl;

		choice = this->getIntChoice();
		system("cls");
		switch (choice)
		{
		case 1:
			FileAnalyzerObj.setAnalyzerMode(0);
			break;

		case 2:
			FileAnalyzerObj.setAnalyzerMode(1);
			break;

		default:
			system("cls");
			return;
			break;
		}

		FileAnalyzerObj.clearStudentData();

		FileAnalyzerObj.setFileName(L"meeting_saved_chat.txt");
		FileAnalyzerObj.readFile();
		FileAnalyzerObj.analyzeFileForStudentNicknames();
		FileAnalyzerObj.coutDATA();

		if (!performTheActionAgain(L"Венуться к меню анализатора файла?")) {
			system("cls");
			return;
		}

	}
}



int Menu::getIntChoice() {
	int choice;
	this->clearCin();
	wcout << endl;
	wcout << L"Ваш выбор: ";
	wcin >> choice;

	return choice;
}

void Menu::clearCin() {
	wcin.clear();
	wcin.ignore(wcin.rdbuf()->in_avail());
}

bool Menu::performTheActionAgain(wstring message) {
	wcout << endl;
	wcout << message << endl
		<< L"1 - Да\n"
		<< L"2 - Нет"
		<< endl;
	if (this->getIntChoice() == 1) {
		system("cls");
		return true;
	}
	else {
		system("cls");
		return false;
	}
}