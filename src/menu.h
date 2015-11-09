#ifndef MENU_H_
#define MENU_H_

#include <fstream>
#include <sstream>
#include <iostream>
#include <windows.h>
//#include <conio.h>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#include "auxiliar.h"
#include "ficheiros.h"
#include "empresa.h"
#include "strings.h"
#include "ficheiros.h"

using namespace std;

/****************************************************************************************************
 * 												AUXILIAR											*
 ****************************************************************************************************/
/**
 * Error class (for throwing purpose).
 */
template<class T, class N>
class Erro_Menu {
public:
	T erro;													/**< Error. */
	N valor;												/**< Extra value to send (if necessary). */
	Erro_Menu(T erro, N valor): erro(erro), valor(valor) {}		/**< Constructor. */
	Erro_Menu(T erro): erro(erro), valor(NULL) {}				/**< Constructor (without extra value). */
};
/**
 * Initializes the maps with the options of the menu.
 */
void OptionsInit();
/**
 * Initializes the vector with the professions.
 */
void ProfessInit();
/**
 * Clears the screen, removes the cursor and sets the text color to grey.
 */
void ScreenInit();
/**
 * Prints the options related to a certain sub-menu of UPDATE option.
 */
size_t coutUPDATE(const size_t subOP);
/**
 * Handles the options related to a certain sub-menu of UPDATE option.
 */
size_t handleUPDATE(const size_t subOP, const size_t ch);
/****************************************************************************************************
 * 												PRINT_MENUS											*
 ****************************************************************************************************/
/**
 * Prints a title.
 * @param toShow string Title to print.
 * @param toClearScreen bool Defines if the program should or not clear the Screen upon this print.
 */
void printTitleMenu(const string toShow, const bool toClearScreen);
/**
 * Prints the main menu title.
 * @param op size_t Selected option.
 * @param faded bool If the main menu is not the current selection, all options will appear slightly faded.
 */
void printMenu(const size_t op, const bool faded);
/**
 * Prints the sub-menus.
 * @param op size_t Selected option.
 * @param subOP size_t Selected sub-option.
 */
void printMenu(const size_t op, const size_t subOP);
/**
 * Prints the initial menu title.
 * @param op size_t Selected option.
 */
void printMenu(const size_t op);
/**
 * Prints the titles within the sub-menus.
 * @param toShow string Title to print.
 * @param text bool If true, then the escape method will be in a getline(), otherwise it will be handled with getch().
 */
void printSubMenu(const string toShow, const bool text, const bool toClearScreen);
/****************************************************************************************************
 * 												CREATE												*
 ****************************************************************************************************/
/**
 * Creates a new Condo - receives from the user the necessary variables.
 * @return true In case of sucess.
 */
bool createNewCondo(Company &e1);
/**
 * Creates a new Property - receives from the user the necessary variables.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool createNewProp(Company &e1);
/**
 * Creates a new Technician - receives from the user the necessary variables.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool createNewTec(Company &e1);
/**
 * Creates a new Owner - receives from the user the necessary variables.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool createNewOwner(Company &e1);
/**
 * Creates a new Contract - receives from the user the necessary variables.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool createNewContr(Company &e1);
/****************************************************************************************************
 * 												 UPDATE												*
 ****************************************************************************************************/
/**
 * Updates the Company:
 *  - name
 * 	- balance
 * 	- date
 *
 * @param toDo Action to be performed.
 * @param e1 Company.
 * @return true In case of sucess.
 */
int editEmpresa(const size_t toDo, Company &e1);
/**
 * Updates a Condo:
 *  - remove:
 *  	- condo
 *  	- properties
 *
 * @param toDo Action to be performed.
 * @param index Condo's index.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool editCondo(const size_t toDo, const size_t index, Company &e1);
/**
 * Updates a Technician:
 *  - name
 *  - profession
 *  - salary
 *
 * @param toDo Action to be performed.
 * @param index Technician's index.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool editTec(const size_t toDo, const size_t index, Company &e1);
/**
 * Updates an Owner:
 * 	- name
 *  - remove
 *
 * @param toDo Action to be performed.
 * @param index Owner's index.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool editOwner(const size_t toDo, const size_t index, Company &e1);
/**
 * Updates a Property:
 * 	- remove:
 * 		- contract
 * 		- property
 *
 * @param toDo Action to be performed.
 * @param indexCondo Condo's index.
 * @param indexProp Property's index.
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool editProp(const size_t toDo, const size_t indexCondo, const size_t indexProp, Company &e1);
/****************************************************************************************************
 * 												PRINT												*
 ****************************************************************************************************/
/**
 * Sub-menu that allows the user to select the Condo which's properties are to be printed.
 * @param e1 Company.
 * @return size_t Condo's index.
 */
size_t selectCondo(vector<string> &vars, Company &e1);
/****************************************************************************************************
 * 												SEARCH											*
 ****************************************************************************************************/
/**
 * Searches a Tehcnician (by one of this parameters):
 * 	- profession
 * 	- name
 * 	- salary (interval)
 *
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool searchTec(Company &e1);
/**
 * Searches an Owner:
 * 	- name
 *
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool searchOwner(Company &e1);
/**
 * Searches a Property (by one of this parameters):
 * 	- type
 * 	- area (interval)
 * 	- floor (interval)
 *
 * @param e1 Company.
 * @return true In case of sucess.
 */
bool searchProp(Company &e1);
/****************************************************************************************************
 * 												MENUS												*
 ****************************************************************************************************/
/**
 * Reservation confirmation menu.
 * @param condo_id ID of the condo to confirm.
 * @return Action to do. ( FALSE - CANCEL ; TRUE - CONFIRM )
 */
bool confirmReservation(const Reservation & r);
/**
 * Handles the sub-menu of Edit/Update.
 * @param op size_t Selected option frow the previous menu.
 * @param e1 Company.
 * @return <not used>
 */
bool menu4(const size_t subOP, Company &e1);
/**
 * Handles the sub-menus.
 * @param op size_t Selected option frow the previous menu.
 * @param e1 Company.
 * @return <not used>
 */
bool menu3(const size_t op, Company &e1);
/**
 * Handles the main menu.
 * @param e1 Company.
 * @return <not used>
 */
bool menu2(Company &e1);
/**
 * Intial menu. Creates or loads a Company.
 */
void menu1();
/****************************************************************************************************
 * 											EXT INSPECTION											*
 ****************************************************************************************************/
void callExtInspection( Company & c, int condo_id);

#endif /* MENU_H_ */
