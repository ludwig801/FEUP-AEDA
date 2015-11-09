/*
 * auxiliar.cpp
 *
 *  Created on: 31 de Out de 2013
 *      Author: Luis
 */

#include "auxiliar.h"


void removeCursor() {
	// Variables
	CONSOLE_CURSOR_INFO cursorInfo; // Cursor info struct
	HANDLE cursorOut = GetStdHandle(STD_OUTPUT_HANDLE); //Handle for the cursor

	// New cursor info
	cursorInfo.bVisible = false; // invisible
	cursorInfo.dwSize = 1;

	// Sets cursor attributes
	SetConsoleCursorInfo(cursorOut,&cursorInfo);
}

void clearScreen() {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD cCharsWritten;
	DWORD dwConSize;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coordScreen = { 0, 0 };

	//hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if(hStdout == INVALID_HANDLE_VALUE)
		return;

	if(!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if(!FillConsoleOutputCharacter(hStdout, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	if(!FillConsoleOutputAttribute(hStdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	SetConsoleCursorPosition( hStdout, coordScreen );
}

int readkey() {
	return _getch();
}

void changeTextColor(const int col) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE) {
		cout << "Error while getting input handle" << endl;
		return;
	}
	//sets the color to intense red on blue background
	SetConsoleTextAttribute(hStdout, col);
}

bool IsStringNumber(const string &var) {
	size_t index = 0;
	while(index != var.length()) {
		if(! ((var[index] >= '0') && (var[index] <= '9')) ) {
			return false;
		}
		index++;
		if(index == var.length()) {
			return true;
		}
	}
	return false;
}

bool IsStringName(const string &var) {
	size_t index = 0;
	while(index != var.length()) {
		if(! ( ((var[index] >= 'A') && (var[index] <= 'Z')) ||
			   ((var[index] >= 'a') && (var[index] <= 'z')) ||
			   (var[index] == ' ') )){
			return false;
		}
		index++;
		if(index == var.length()) {
			return true;
		}
	}
	return false;
}

bool IsStringProfession(const string & var) {

	vector<string> profs; profs.push_back("Alvenaria"); profs.push_back("Eletricista");
	profs.push_back("Infra-estruturas"); profs.push_back("Espacos Comuns");
	profs.push_back("Pintura"); profs.push_back("Limpeza");

	for(vector<string>::iterator it = profs.begin(); it != profs.end(); ++it) {
		if(var.compare(*it) == 0) return true;
	}

	return false;

}

bool IsStringExit(const string &var) {
	return (var == "exit");
}

bool IsStringEmpty(const string &var) {
	return (var == "");
}

bool IsStringNull(const string &var) {
	return (var == "null");
}

void clearCinStream() {
	cin.clear();
	cin.ignore(100, '\n');
}

string criaNomeRelatorio(const size_t & year) {

	stringstream nome;
	nome << LOG;

	if(year < 10) nome << "_00";
	else if(year < 100) nome << "_0";
	else nome << "_";

	nome << year << ".csv";

	return nome.str();

}

void waitForUser() {

	cout << "Pressione qualquer tecla para continuar..." << endl << endl;
	 _getch();

}
