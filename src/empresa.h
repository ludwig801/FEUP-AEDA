#ifndef EMPRESA_H_
#define EMPRESA_H_

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <tr1/unordered_set>

#include "pessoa.h"
#include "condominio.h"
#include "auxiliar.h"
#include "strings.h"
#include "BST.h"
#include "extInspection.h"
#include "Reservation.h"
#include "menu.h"

using namespace std;

struct condosHash {

	int operator() (const Condo * co) const {
		return co->getID();
	}

	bool operator() (const Condo * co1, const Condo * co2) const {
		return (*co1 == *co2);
	}
};

typedef tr1::unordered_set<Condo *, condosHash, condosHash> HashCondos;
typedef priority_queue<Reservation> HEAP_SALOON;


/**
 * Hash Condo error class.
 */
class HashCondos_Error {
public:
	HashCondos_Error() {}
};

/**
 * Error class. Used for throws.
 */
template<class T, class N>
class Company_Error {
public:
	T error;															/**< Error. */
	N value;															/**< Extra value if needed. */
	Company_Error(T error, N value): error(error), value(value) {}		/**< Constructor with extra value. */
	Company_Error(T error): error(error), value(0) {}					/**< Constructor. */
};

/**
 *
 * Class Company. Contains all Condos, Technicians and Owners.
 *
 */
class Company {
protected:

	string name;										/**< Name. */
	long int balance;									/**< Balance. */
	int month;										/**< Current Month. */
	int year;										/**< Current Year. */

	int confirmationLimit;								/**< Months before event the condo must confirm the reservation (limit). */

	map<pair<int, int>, int> total_wages;				/**< Total spent on wages. <year, month> <type, cost> */
	map<pair<int, int>, vector<pair<string, int> > > total_inspections;			/**< Total spent on inspection. <year, month> <type, cost> */

	pair<int, int> startingDate; 						/**< Starting year and month, when the program was started. */

	map<pair<int, int>, pair<int, bool> > events;		/**< Events organized by condos. <year, month>, <condo_id, realized> */

	vector<Technician * > technicians; 					/**< Set of Technicians */
	vector<Condo * > condos;							/**< Set of Condos. */
	vector<Owner * > owners; 							/**< Set of Owners. */

	map<string, pair<size_t, size_t> > inspections;		/**< Map with the periodicity of each inspection (by profession). */
	map<string, size_t> periodicity_default; 			/**< Map with the default periodicity of each inspection (by profession). */

	BST<ExtInspection> extInspectionsBST;				/**< Binary search tree of the external inspections. */

	HashCondos oldCondos;								/**< Hash table of all the old condos. */

	HEAP_SALOON saloon;									/**< All the reserves for the events saloon. */

	size_t MAX_VARIATION;								/**< Maximum external inspections price variations. */


	/* Last minute implementations */
	priority_queue<int> free_condo_ids;					/**< All the ID's for the condos, that get free to use again. (After removing from old condos). */

public:

	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Default constructor.
	 *
	 * Name = "default".
	 * Balance = 0.
	 */
	Company();
	/**
	 * Full Constructor
	 *
	 * @param name Name of the Empresa.
	 * @param balance Balance of the Empresa.
	 * @param month Month.
	 * @param year Year.
	 * @param inspections Map of inspections.
	 * @param periodicity_default Map of inspections periodicity.
	 */
	Company(string name, long int balance, int month, int year,
			map<string, pair<size_t, size_t> > inspections, map<string, size_t> periodicity_default, int confirmationLimit);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Class Destructor.
	 */
	virtual ~Company();
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Gets the name of the Empresa.
	 *
	 * @return Name.
	 */
	string getName() const;
	/**
	 * Gets the balance of the Empresa.
	 *
	 * @return Balance.
	 */
	long int getBalance() const;
	/**
	 * Gets the current month.
	 *
	 * @return Month.
	 */
	int getMonth() const;
	/**
	 * Gets the current year.
	 *
	 * @return Year.
	 */
	int getYear() const;
	/**
	 * @return Initial date
	 */
	pair<int, int> getInitialDate() const;
	/**
	 * Gets Condos.
	 *
	 * @return Vector of Condos.
	 */
	vector<Condo *> getCondos() const;
	/**
	 * Gets Techinicians.
	 *
	 * @return Vector of Techinicians.
	 */
	vector<Technician *> getTechinicians() const;
	/**
	 * Gets Owners.
	 *
	 * @return Vector of Owners.
	 */
	vector<Owner *> getOwners() const;
	/**
	 * Gets inspections.
	 *
	 * @return Map of inspections.
	 */
	map<string, pair<size_t, size_t> > getInspections() const;
	/**
	 * Gets inspections periodicity.
	 *
	 * @return Map of inspections periodicity.
	 */
	map<string, size_t> getPeriodicityDefault() const;
	/**
	 * @return Total spent on wages.
	 */
	map<pair<int, int>, int> getTotalWages() const;
	/**
	 * @return Total spent on inspections.
	 */
	map<pair<int, int>, vector<pair<string, int> > >  getTotalInspections() const;
	/**
	 * @return Confirmation Limit.
	 */
	int getConfirmationLimit() const;
	/**
	 * @return Events map.
	 */
	map<pair<int, int>, pair<int, bool> > getEvents() const;
	/**
	 * @return Free ID's
	 */
	priority_queue<int> getFreeIDs() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Sets the name of the Company.
	 *
	 * @param name.
	 */
	void setName(const string name);
	/**
	 * Sets the balance (only positive) of the Company.
	 *
	 * @param balance New balance of the Company.
	 */
	void setBalance(const size_t balance);
	/**
	 * Sets the month.
	 * @param month New month of the Company.
	 */
	void setMonth(const int & month);
	/**
	 * Sets the year.
	 * @param year New year of the Company..
	 */
	void setYear(const int & year);
	/**
	 * Increments the month.
	 */
	void incrementMonth();
	/**
	 * Increments the year.
	 */
	void incrementYear();
	/**
	 * Sets the name of a Technician.
	 *
	 * @param index Index of the Technician.
	 * @param name Name of the Technician to implement.
	 */
	void setNameTechnician(const size_t & index, const string & name);
	/**
	 * Sets the salary of a Technician.
	 *
	 * @param index Index of the Technician.
	 * @param salary Salary of the Technician to implement.
	 */
	void setSalaryTechnician(const size_t & index, const size_t & Salary);
	/**
	 * Sets confirmation limit.
	 * @param confirmationLimit Confirmation limit.
	 */
	void setConfirmationLimit(const int & confirmationLimit);
	/**
	 * Sets the profession of a Technician.
	 *
	 * @param index	Index of the Technician.
	 * @param profession Profession of the Technician to implement.
	 */
	void setProfessionTechnician(const size_t & index, const string & profession);
	/**
	 * Sets the name of a Owner.
	 *
	 * @param index Index of the Owner.
	 * @param name Name of the Owner to implement.
	 */
	void setNameOwner(const size_t & index, const string & name);
	/**
	 * Sets the inspection periodicity of a certain profession.
	 *
	 * @param key Profession.
	 * @param periodicity Inspection periodicity to implement.
	 */
	void setInspectionPeriodicity(const string & key, const size_t & periodicity);
	/**
	 * Sets the inspection's cost.
	 *
	 * @param key Profession.
	 * @param cost Cost of each inspection to implement.
	 */
	void setInspectionCost(const string & key, const size_t & cost);
	/**
	 * Decrements, for each profession, the remaining months before inspection.
	 */
	void decrementInspections();
	/**
	 * Sets remaining months before next parcel payment (of each property).
	 *
	 * @param index Condo index.
	 * @param id Property index.
	 * @param months Value to be implemented.
	 */
	void setRemainingMonths(const size_t & index, const size_t & id, const size_t & months);
	/**
	 * Inserts the month's technicians salary.
	 * @param year Year
	 * @param month Month
	 * @param cost Spent
	 */
	void insertTotalWages(const int & year, const int & month, const int & wages);
	/**
	 * Inserts the month's inspections cost.
	 * @param year Year
	 * @param month Month
	 * @param cost Spent
	 */
	void insertTotalInspections(const int & year, const int & month, const string & type, const int & cost);
	/**
	 * Inserts event to map.
	 * @param year Year
	 * @param month Month
	 * @param condo_id ID of the Condo
	 * @param realized If it was realized or cancelled.
	 */
	void insertEvent(const int & year, const int & month, const int & condo_id, const bool & realized);
	/**
	 * Inserts a new free id.
	 * @param condo_id id.
	 */
	void insertFreeID(const int & condo_id);
	/**
	 * Remove the first free id.
	 */
	void removeFreeID();
	/*
	 * ==================================
	 *               CONDO
	 * ==================================
	 */
	/**
	 * Creates a new Condo.
	 */
	void createCondo();
	/**
	 * Overload.
	 * @param localization Localization of the Condo.
	 * @param total_properties Total properties of the Condo.
	 */
	void createCondo(int localization, size_t total_properties);
	/**
	 * Overload
	 */
	void createCondo(int & id, int & localization, size_t & total_properties);
	/**
	 * Receives the income from every parcels and adds it to the Company financial balance.
	 */
	void receiveParcels();
	/**
	 * Creates a new Property.
	 *
	 * @param index index of the Condo.
	 * @param area Property area.
	 * @param floor Property floor.
	 * @param type Property type: Residence (1), Store (2) or Office (3).
	 */
	void addProperty(size_t index, size_t area, size_t floor, size_t type);
	/**
	 * Decrements remaining months for payment in every properties.
	 */
	void decrementRemainingMonths();
	/**
	 * Searches a Condo in the Company with a given ID.
	 * @param id ID of the Condo to search.
	 * @return Pointer to searched Condo.
	 */
	Condo * searchCondoByID(const int & id) const;
	/**
	 * Checks if a localization is already occupied by a condo of the company.
	 * @param localization Localization to check.
	 * @return True if the localization is available, False otherwise.
	 */
	bool isLocalizationValid(const int & localization) const;
	/*
	 * ==================================
	 *             TECHNICIAN
	 * ==================================
	 */
	/**
	 * Creates a new Technician.
	 *
	 * @param name Technician name.
	 * @param profession Technician profession.
	 * @param salary Technician salary.
	 */
	void createTechnician(string name, string profession, size_t salary);
	/**
	 * Verifies if there is a name associated with a certain Technician. Name duplication is not accepted in the program.
	 *
	 * @return true if name exists already, false otherwise.
	 */
	bool technicianExists(string name) const;
	/**
	 * Returns the Technician with the name in the parameter.
	 *
	 * @param name Name of the Technician to search.
	 *
	 * @return pointer to the Technician. Obs: if not found, throws an exception.
	 */
	Technician * searchTechnician(string nome) const;
	/**
	 * Deducts all the salaries from the Company balance.
	 */
	void payTechnicians();
	/**
	 * Calls a certain profession. If there is a Technician available, is disponibility is altered.
	 *
	 * @param profissao_index Profession index.
	 * @param index Condo index.
	 * @return true If there's a Technician available.
	 * @return false If there aren't any Technician available.
	 */
	bool callTechnician(const int & profissao_index, const size_t & index);
	/**
	 * Sets all Technicians as available.
	 */
	void setTechniciansAvailable();
	/*
	 * ==================================
	 *               OWNER
	 * ==================================
	 */
	/**
	 * Creates a new Owner in the Company.
	 *
	 * @param name Owner name.
	 */
	void addOwner(string nome);
	/**
	 * Searchs an Owner and returns its index.
	 *
	 * @param name Name to search.
	 * @return index or -1 if not existent.
	 */
	int searchOwner(string nome) const;
	/**
	 * Searches for an Owner and returns a pointer to its instance.
	 *
	 * @param name Name to search.
	 * @return Owner. Throws an 'ERRO_EMPRESA' exception if not found.
	 */
	Owner * getOwner(string nome);
	/**
	 * Associates a contract.
	 *
	 * @param indexCondo Condo index.
	 * @param indexProperty Property index.
	 * @param indexOwner Owner index.
	 * @param type Contract type.
	 */
	void createContract(const size_t & index, const size_t & indexProperty, const size_t & indexOwner,
			const size_t & type);
	/*
	 * ==================================
	 *              REMOVE
	 * ==================================
	 */
	/**
	 * Removes a Condo.
	 *
	 * @param index Condo index.
	 */
	void removeCondo(const int & condo_id);
	/**
	 * Removes a Property.
	 *
	 * @param index Condo index.
	 * @param indexProperty Property index.
	 */
	void removeProperty(const size_t & index, const size_t & indexProperty);
	/**
	 * Removes an associated contract, therefore leaving the Property vacant.
	 *
	 * @param index Condominios's index.
	 * @param indexProperty Property index in the Condo properties vector.
	 */
	void removePropertyContract(const size_t & index, const size_t & indexProperty);
	/**
	 * Removes all Properties from a Condo.
	 *
	 * @param c Pointer to Condo instance.
	 */
	void removeAllPropertiesFromCondo(Condo * c);
	/**
	 * Removes a Owner.
	 *
	 * @param index Owner index.
	 */
	void removeOwner(const size_t & index);
	/**
	 * Removes all contracts belonging to a Owner.
	 *
	 * @param index Owner index.
	 */
	void removeContracts(size_t & index);
	/**
	 * Removes a Technician.
	 *
	 * @param index Technician index.
	 */
	void removeTechnician(const size_t & index);
	/**
	 * Removes all properties from a Condo belonging to a certain Owner.
	 *
	 * @param index Condo index.
	 */
	void removePropertiesFromOwner(const int & condo_id);
	/*
	 * ==================================
	 *            SIMULATION
	 * ==================================
	 */
	/**
	 * Simulates a time interval in the Empresa, using the amount of months is provided by the user.
	 *
	 * The simulation receives all the parcels belonging to all Propriedades, pays all salaries,
	 *  pays all inspections and checks for random events, such as the calling for a Tecnico.
	 * After each month simulation the balance of the Empresa is updated.
	 *
	 * @param number Number of months to simulate.
	 */
	void simulate(const size_t & number);
	/**
	 * Sets the next month parameters, doing so by incrementing the current date and
	 * decrementing in every Propriedade the remaining months for payment.
	 */
	void prepareMonth();
	/**
	 * Conducts the inspections.
	 * On the pratical aspect, it only afects the Empresa's balance, discounting the inspections cost.
	 */
	void makeInspections();
	/**
	 * Calculates (randomly) the expenses with common spaces of each Condominio.
	 * It is directly dependant on the number of Porpriedades of that Condominio.
	 *
	 * @param index Condominio's index.
	 */
	void commonSpacesExpenses(const size_t & index);
	/**
	 * Calls (randomly) a Tecnico's services.
	 *
	 * @param index Index of the Condominio that might call a technical service.
	 */
	void callTechnicianRandomly(const size_t & index);
	/**
	 * Handles random events.
	 */
	void randomEvents();
	/**
	 * Writes financial logs from condos to file.
	 */
	void writeFinancialLogs();
	/**
	 * Writes month title to file.
	 */
	void writeMonth(ostream & file, const int & month);
	/**
	 * Saves financial log to file.
	 */
	void saveLog();
	/**
	 * Saves Technicians wages to file.
	 */
	void writeTechniciansWages(ofstream & file, const int & year, const int & month);
	/**
	 * Saves Inspections cost to file.
	 */
	void writeTotalInspections(ofstream & file, const int & year, const int & month);
	/**
	 * Saves events to file.
	 */
	void writeEvents(ofstream & file, const int & year, const int & month, const int & condo_id);
	/*
	 * ==================================
	 *          EXT. INSPECTIONS
	 * ==================================
	 */
	/**
	 * @return BST with external inspections companies.
	 */
	BST<ExtInspection> getExtInspectionsBST() const;
	/**
	 * Adds a new external inspection (node) to the BST.
	 * @param e Instance of ExtInspection.
	 */
	void addExtInspectionToBST(ExtInspection & e);
	/**
	 * Removes external inspection (node) from the BST.
	 * @param e Instance of ExtInspection.
	 */
	void removeExtInspectionFromBST(ExtInspection & e);
	/**
	 * Prints all the external inspections (sorted) that are in the BST.
	 */
	void printExtInspections() const;
	/**
	 * @return true if the external inspections BST is empty, false otherwise.
	 */
	bool isExtInspectionsEmpty() const;
	/**
	 * @return Iterator In-Order for the External Inspections BST.
	 */
	BSTItrIn<ExtInspection> getBSTIteratorIn() const;
	/**
	 * Calls a external inspection for condo.
	 * @param index Index of the condo calling the ext inspection.
	 * @param e Pointer to ExtInspection called.
	 */
	size_t callExtInspection(ExtInspection * e);
	/*
	 * ==================================
	 *             HASH TABLE
	 * ==================================
	 */
	/**
	 * @return Old Condos hash table.
	 */
	HashCondos getOldCondosHashTable() const;
	/**
	 * Adds a condo to the old condos hash table.
	 * @param co Condo instance.
	 */
	void addCondoToOldCondos(Condo & co);
	/**
	 * Removes Condo from old condos hash table.
	 * @param co Condo instance.
	 */
	void removeCondoFromOldCondos(Condo & co);
	/**
	 * @param co Condo to search.
	 * @return Condo from Hash Table at a given index.
	 */
	Condo * getOldCondoFromHashTable(Condo & co) const;

	/*
	 * ==================================
	 *            PRIORITY QUEUE
	 * ==================================
	 */
	HEAP_SALOON getSaloonReservations() const;
	void addReservation(Reservation & r);
	void removeReservation(Reservation & r);
	/**
	 * Validates all the reservations in the priority queue.
	 *    Verifices if the confirmation limit is still valid.
	 * @return condo_id and false if that condo needs to confirm urgently.
	 */
	pair<Reservation, bool> validateReservations();
	/**
	 * Deletes all reservation from a given condo.
	 * @param condo_id ID of the Condo.
	 */
	void removeAllReservationsFromCondo(const int & condo_id);
	/**
	 * @param year Year
	 * @param month Month
	 * @return True if a given date is a valid date, false otherwise.
	 */
	bool validDate(const int & year, const int & month) const;
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Implements the = operator in the class Empresa.
	 */
	Company & operator= (const Company & e);
	/**
	 * Implements the << operator in the class Empresa.
	 */
	friend ostream & operator<<(ostream & o, const Company & e);
};


#endif /* EMPRESA_H_ */
