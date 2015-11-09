/**
 * CONDOMINIO.h
 *
 *  Created on: 9 de Out de 2013
 *      Author: ei12054
 *
 */

#ifndef CONDOMINIO_H_
#define CONDOMINIO_H_

#include <string>
#include <iostream>
#include <vector>
#include <map>

#include "propriedade.h"
#include "extInspection.h"
#include "BST.h"

using namespace std;

enum PROPERTY_TYPES { RESIDENCE, STORE, OFFICE };

/* Forward declaration of Company. */
class Company;

/**
 * Class Condominio. Contains the properties of each instance of Condominio.
 */
class Condo {
protected:

	vector<Property *> propriedades; 								/**< Vector of Properties belonging to the Condominio. */

	int id;															/**< Internal identification of the condo. */
	int localization;												/**< Localization of the condo. */
	size_t total_properties;										/**< Total properties that the condo had since the begining. */

	// FINANCIAL LOG
	map<pair<int, int>, int> profit;								/* Profit of every month of the current year. */
	map<pair<int, int>, int> expenses;								/* Expenses of every month of the current year. */
	map<pair<int, int>, vector<pair<int, int> > > techServices;		/* Technical services call. <year, month>, <service, price>. */
	map<pair<int, int>, int> commonSpacesExpenses;					/*< Common Spaces Expenses. <year, month>, cost */
	map<pair<int, int>, vector<pair<string, int> > > extInspectionsCalls;  /*< External inspections called. <year, month>, <name, cost>. */

	static int last_id;												/**< ID of the last Condo created by the Company. */

public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Default constructor.
	 */
	Condo();
	/**
	 * Constructor with ID only.
	 */
	Condo(int & id);
	/**
	 * Complete constructor, without ID.
	 */
	Condo(int & localization, size_t & total_properties);
	/**
	 * Complete constructor, with ID.
	 */
	Condo(int & id, int & localization, size_t & total_properties);
	/*
	 * ==================================
	 * ==================================
	 */
	/*
	 * ==================================
	 *             DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destructor.
	 */
	~Condo();
	/*
	 * ==================================
	 * ==================================
	 */
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * @return ID of the Condo.
	 */
	int getID() const;
	/**
	 * @return Last ID.
	 */
	static int getLastID();
	/**
	 * @return Localization of the condo.
	 */
	int getLocalization() const;
	/**
	 * @return Total properties of the condo.
	 */
	size_t getTotalProperties() const;
	/**
	 * @return Vector of properties.
	 */
	vector<Property *> getPropriedades() const;
	/**
	 * @return Total value of the condo.
	 */
	size_t getTotalValue() const;
	/**
	 * @return Profit map.
	 */
	map<pair<int, int>, int> getProfit() const;
	/**
	 * @return Expenses map.
	 */
	map<pair<int, int>, int> getExpenses() const;
	/**
	 * @return Technical services map
	 */
	map<pair<int, int>, vector<pair<int, int> > > getTechServices() const;
	/**
	 * @return Common Spaces Expenses.
	 */
	map<pair<int, int>, int> getCommonSpacesExpenses() const;
	/**
	 * @return ExtInspections calls.
	 */
	map<pair<int, int>, vector<pair<string, int> > > getExtInspectionsCalls() const;
	/*
	 * ==================================
	 * ==================================
	 */
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Sets a new localization for the condo.
	 * @param localization Localization.
	 */
	void setLocalization(int & localization);
	/**
	 * Sets a value for the total properties of the condo.
	 * @param total_properties Total properties.
	 */
	void setTotalProperites(size_t & total_properties);
	/**
	 * Adds a new property to the Condominio.
	 * @param index Condominios's index.
	 * @param area Property's area.
	 * @param floor Property's floor.
	 * @param type Property's type.
	 */
	void addProperty(const size_t & index, const size_t & area, const size_t & floor, const size_t & type);
	/**
	 * Removes a property.
	 * @param index Index of the property to remove.
	 */
	void eliminaPropriedade(const size_t & index);
	/**
	 * Removes all properties from the Condominio.
	 */
	void eliminaTodasPropriedades();
	/**
	 * Removes a contract from a property.
	 * @param index Index of the property.
	 */
	void eliminaContratoPropriedade(const size_t & index);
	/**
	 * Associates a contract to a property.
	 * @param index Property's index.
	 * @param tipoContrato Type of contract.
	 * @param p proprietary of the property.
	 */
	void criaContrato(const size_t & index, const size_t & tipoContrato, Owner * p);
	/**
	 * Decrements in all properties the remaining months in the contract before the next payment.
	 */
	void decrementaMesesRestantes();
	/**
	 * Resets the remaining months before next payment.
	 * Value to reset to, depending on the contract:
	 * 	Monthly:		1
	 * 	Semiannual:		6
	 * 	Yearly:			12
	 *
	 * 	This function is called immediatly after the prior is computed.
	 *
	 * @param index Property's index.
	 */
	void resetMesesRestantes(const size_t & index);
	/**
	 * Sets the remaining months before payment.
	 * @param index Property's index.
	 * @param meses Number of months to set.
	 */
	void setMesesRestantes(const size_t & index, const size_t & meses);
	/**
	 * Returns the number of free properties in the Condominio.
	 * @param none.
	 * @return Number of free properties.
	 */
	size_t getNumPropriedadesLivres();
	/**
	 * Increments the total properties by one.
	 */
	void incrementTotalProperties();
	/**
	 * Decrements the total properties by one.
	 */
	void decrementTotalProperties();
	/**
	 * Increments the last id by one.
	 */
	void incrementLastID();
	/**
	 * Decrements the last id by one.
	 */
	void decrementLastID();
	/**
	 * Inserts month profit to map.
	 * @param year Year.
	 * @param month Month.
	 * @param profit Profit.
	 */
	void insertProfit(const int & year, const int & month, const int & value);
	/**
	 * Inserts month expenses to map.
	 * @param year Year.
	 * @param month Month.
	 * @param expenses Expenses.
	 */
	void insertExpenses(const int & year, const int & month, const int & value);
	/**
	 * Inserts technical service call to map.
	 * @param year Year.
	 * @param month Month.
	 * @param service Type of service.
	 * @param cost Cost of the service.
	 */
	void insertTechService(const int & year, const int & month, const int & service, const int & cost);
	/**
	 * Inserts Common Spaces Expense.
	 * @param year Year.
	 * @param month Month.
	 * @param expenses Expenses.
	 */
	void insertCommonSpacesExpenses(const int & year, const int & month, const int & expenses);
	/**
	 * Inserts Ext Inspection Call.
	 * @param year Year
	 * @param month Month
	 * @param name Type of inspection.
	 * @param cost Cost of the inspection.
	 */
	void insertExtInspectionCall(const int & year, const int & month, const string & name, const int & cost);
	/**
	 * Clears profit, expenses and technical services maps.
	 */
	void clearsFinancialLog();
	/**
	 * Writes all condos profit to file.
	 */
	void writeCondoProfit(ofstream & file, const int & year, const int & month);
	/**
	 * Writes all condos expenses to file.
	 */
	void writeCondoExpenses(ofstream & file, const int & year, const int & month);
	/**
	 * Writes services to file.
	 */
	void writeServices(ofstream & file, const int & year, const int & month);
	/**
	 * Writes Common Spaces Expenses to file.
	 */
	void writeCommonSpacesExpenses(ofstream & file, const int & year, const int & month);
	/**
	 * Writes Ext Inspections calls to file.
	 * @param file Ofstream of the file to write.
	 * @param year Year
	 * @param month Month
	 */
	void writeExtInspectionsCalls(ofstream & file, const int & year, const int & month);
	/*
	 * ==================================
	 * ==================================
	 */

	/**
	 * Search for the best external company to provide a type of inspection to the condo.
	 * The best external company criteria by default, is the closest one.
	 * @param c Instance of the main company.
	 * @param type Type of inspection to search.
	 * @param byPrice True if the searching criteria is the cheapest. False by default (closest will be the criteria).
	 * @return Pointer to ExtInspection that matches the criteria.
	 */
	ExtInspection * searchBestExtInspection(const Company & c, const string & type, bool byPrice = false) const;

	bool operator== (const Condo & co) const;

	/**
	 * Implements the << operator in the class Condo.
	 */
	friend ostream & operator<<(ostream & o, const Condo & c);


};


#endif /* CONDOMINIO_H_ */
