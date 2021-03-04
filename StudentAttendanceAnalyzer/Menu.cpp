#include "Menu.h"

Menu::Menu() { version = 2; }
Menu::~Menu() {}

void Menu::openMainMenu() {
	int choice;


	while (true)
	{
		wcout << L"StudentAttendanceAnalyzer V" << version << " by MarZon\n" << endl;

		wcout << L"[������� ����]\n\n";
		wcout << L"�������� ������������ �����:\n"
			<< L"1 - ���������������� ����\n"
			<< L"2 - ���������� ���������� ��������� ������� �����\n"
			//<< L"������� ������ � ���� (��� �� �����������)" 
			<< L"����� ������ ����� - ����� �� ���������"
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
				wcout << L"[���������] �� ��� �� ������������� ����!" << endl;

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

		wcout << L"[���� ����������� �����]\n\n";
		wcout << L"�������� ������ ������:\n"
			<< L"1 - ������� 1\n"
			<< L"2 - ������� 2\n"
			<< L"����� ������ ����� - ��������� �����"
			<< endl;

		wcout << endl;
		wcout << L"�������� ���������:\n"
			<< L"������� 1:\n"
			<< L"��:��:��	 ��  ����������� : ��������� ��������\n"
			<< L"��:��:��	 ��  �����������  ����  �����������(�������) : ��������� ��������\n"
			<< L"������� 2:\n"
			<< L"��:��:��	�����������:	��������� ��������"
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

		if (!performTheActionAgain(L"�������� � ���� ����������� �����?")) {
			system("cls");
			return;
		}

	}
}



int Menu::getIntChoice() {
	int choice;
	this->clearCin();
	wcout << endl;
	wcout << L"��� �����: ";
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
		<< L"1 - ��\n"
		<< L"2 - ���"
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