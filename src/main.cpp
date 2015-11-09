#include <iostream>
#include "time.h"

#include "empresa.h"
#include "pessoa.h"
#include "condominio.h"
#include "auxiliar.h"
#include "menu.h"
#include "strings.h"
#include "ficheiros.h"

using namespace std;

/**
 * Tests for the first topic of the second part of the project.
 * No need for further details.
 *
 * BST!!!
 */
void secondPartFirstTopic() {

	// ExtInspection instances
	ExtInspection e1("Carvalhos", 1, "Alvenaria", 200);
	ExtInspection e2("Modelo", 2, "Pintura", 500);
	ExtInspection e3("TT", 3, "Pintura", 600);
	ExtInspection e4("BMW", 2, "Limpeza", 300);

	cout << "Starting tests..." << endl;

	Company c;

	c.addExtInspectionToBST(e1);
	c.addExtInspectionToBST(e2);
	c.addExtInspectionToBST(e3);
	c.addExtInspectionToBST(e4);

	saveExtInspections(c); cout << "Saved." << endl;

	c.removeExtInspectionFromBST(e3);

	saveExtInspections(c); cout << "Saved." << endl;

	Company b;

	loadExtInspections(b); cout << "Loaded." << endl;

	b.printExtInspections();

	cout << "Terminated." << endl;

}

void saveReservationsToFileTest() {

	Company c;

	c.createCondo(1, 0);
	c.createCondo(2, 0);
	c.createCondo(3, 0);

	int area = 200, floor = 1, index = 1, type = 1;
	c.addProperty(index, area, floor, type);
	area = 500;
	index = 2;
	c.addProperty(index, area, floor, type);
	c.addProperty(index, area, floor, type);

	int month = 2, year = 2;
	Reservation r1(c.getCondos()[0], month, year);
	Reservation r3(c.getCondos()[2], month, year);
	Reservation r2(c.getCondos()[1], month, year);

	c.addReservation(r1);
	c.addReservation(r3);
	c.addReservation(r2);

	// Prints Reservations
	HEAP_SALOON tmp = c.getSaloonReservations();
	while(!tmp.empty()) {
		cout << tmp.top().getCondo()->getTotalProperties() << endl;
		tmp.pop();
	}

	saveReservations(c);
	gravaCondominios(c);

}

int main() {

	srand (time(NULL));

	/* Menu inicial */
	menu1();

	return 0;
}



