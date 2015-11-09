/**
 * AUXILIAR.h
 *
 *  Created on: 30 de Out de 2013
 *      Author: ei12054
 *
 */
#ifndef AUXILIAR_H_
#define AUXILIAR_H_

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
#include <conio.h>

#include "empresa.h"
#include "pessoa.h"

using namespace std;

/**
 * Removes console's cursor.
 */
void removeCursor();
/**
 * Clears the console.
 */
void clearScreen();
/**
 * Waits for the user to press a key.
 * @return code of the pressed key.
 */
int readkey();
/**
 * Changes console's color.
 * @param col Color code.
 */
void changeTextColor(const int col);
/**
 * Checks if a string is composed with 0-9 digits
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringNumber(const string & var);
/**
 * Checks if a string is composed with A-Z (or a-z) digits.
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringName(const string & var);
/**
 * Checks if a string is composed with A-Z (or a-z) digits
 * and if is a valid a profession.
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringProfession(const string & var);
/**
 * Checks if a string is "exit".
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringExit(const string & var);
/**
 * Checks if a string is empty.
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringEmpty(const string & var);
/**
 * Checks if a string is "null".
 * @param var String to be tested.
 * @return true if valid.
 */
bool IsStringNull(const string & var);
/**
 * Clears the input stream, avoiding reading trash.
 */
void clearCinStream();
/**
 * Creates the name of the yearly report.
 * @param size_t year Current year.
 * @return Name of the report.
 */
string criaNomeRelatorio(const size_t & year);
/**
 * Creates the name of the yearly report relating to called tecnical services.
 * @param size_t year Current year.
 * @return Name of the report.
 */
string criaNomeServicos(const size_t & year);
/**
 * Waits for user to press a key and prints a message.
 */
void waitForUser();

#endif /* AUXILIAR_H_ */
