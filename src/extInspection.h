/*
 * extInspection.h
 *
 *  Created on: 30 de Nov de 2013
 *      Author: Kevin
 */

#ifndef EXTINSPECTION_H_
#define EXTINSPECTION_H_

#include <string>
#include <stdlib.h>

#include "BST.h"

using namespace std;

/**
 * Error class of the external company main class.
 * Handles the error that can be thrown by the main class (ExtInspection).
 */
class ExtInspection_Error {

};

/**
 * The class ExtInspection works like a node for the binary tree. Since each node will have different
 * members its better to keep them organized in a proper class.
 *
 * Also, its better to implement custom operator, needed to work with the binary tree.
 *
 */
class ExtInspection {
protected:

	string name;					/**< Name of the external company. */
	int localization;				/**< Localization of the external company, in x coordinates. */
	string inspectionType;			/**< Type of inspection that the external company provides. */
	size_t price;					/**< Price of the inspection service provided by the ext. company. (Last price provided). */
	string email;					/**< Email of the external company. */

public:

	/**
	 * Default constructor.
	 */
	ExtInspection() : name(""), localization(0), inspectionType(""), price(0), email("") {}

	/**
	 * Main ExtInspection constructor.
	 *
	 * @param inspectionType Type of inspection that is provided.
	 * @param price Price of the provided inspection.
	 */
	ExtInspection(string name, int localization, string inspectionType, size_t price) :
		name(name), localization(localization), inspectionType(inspectionType), price(price) {

		email = name + "@gmail.com";

	}
	/**
	 * Empty ExtInspection destructor.
	 */
	~ExtInspection() {}
	/**
	 * @return Name of the external company.
	 */
	string getName() const { return name; }
	/**
	 * @return Email of the external company.
	 */
	string getEmail() const { return email; }
	/**
	 * @return Localization of the external company.
	 */
	int getLocalization() const { return localization; }
	/**
	 * @return Type of inspection that is provided.
	 */
	string getInspectionType() const { return inspectionType; }
	/**
	 * @return Price of the provided inspection.
	 */
	size_t getPrice() const { return price; }
	/**
	 * Changes external inspection name.
	 * @param name New name.
	 */
	void setName(string & name) { this->name = name; }
	/**
	 * Changes the inspection type.
	 * @param inspectionType New type of inspection provided by the external company.
	 */
	void setInspectionType(string & inspectionType) { this->inspectionType = inspectionType; }
	/**
	 * Changes the price of each inspection provided by the external company.
	 * Only accepts prices bigger than 0 (zero).
	 * @param price New price of the inspection provided by the external company.
	 */
	void setPrice(size_t & price) { if(price > 0) this->price = price; }
	/**
	 * Changes the localization of the external inspection company.
	 * @param localization New localization.
	 */
	void setLocalization(int & localization) { this->localization = localization; }
	/**
	 * Randomly changes the price of the inspection provided by the external company.
	 * Used when calling the company to provide a service.
	 * Member price changed accordingly.
	 * @param max_variation Maximum variation, in %, for the price according to the last price.
	 * 			Default value: 50%.
	 * @return Price of the inspection.
	 */
	size_t randomizeNewPrice(size_t max_variation = 50) {

		int signal = rand() % 2; /* 0 - Positive, 1 - Negative. */

		/*
		 * Formula => Price = Price +/- ( Last_Price * rand() % (max_variation + 1) / 100)
		 */
		if(signal) price += price * (( rand() % (max_variation + 1) ) / 100.0);
		else price -= price * (( rand() % (max_variation + 1) ) / 100.0);

		return price;

	}

	bool operator< (const ExtInspection & e) const {

		if(price != e.price) return price < e.price;
		if(localization != e.localization) return localization < e.localization;
		else return name < e.name;

	}

	friend ostream & operator<< (ostream & o, const ExtInspection & e) {

		o << " " << e.name << ", " << e.inspectionType << ", " << " <" << e.email << "> ";
		o << endl << "   Preco: " << e.price;
		o << endl << "   Local: " << e.localization;

		return o;
	}


};

#endif /* EXTINSPECTION_H_ */
