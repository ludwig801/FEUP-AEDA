/*
 * ficheiros.h
 *
 *  Created on: 6 de Nov de 2013
 *      Author: Kevin Amorim
 */

#ifndef FICHEIROS_H_
#define FICHEIROS_H_

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "auxiliar.h"
#include "empresa.h"
#include "strings.h"
#include "BST.h"
#include "extInspection.h"

using namespace std;


class FileError {
private:
	string filename;

public:
	FileError(string filename) : filename(filename) {}
	string getFilename() const { return this->filename; }

};

class FileCorrupted {
private:
	string filename;
	int line_number;

public:
	FileCorrupted(string filename) : filename(filename), line_number(0) {}
	FileCorrupted(string filename, int line_number) : filename(filename), line_number(line_number) {}
	string getFilename() const { return this->filename; }
	int getLineNumber() const { return this->line_number; }

};
/*
 * ================================================
 *                     FILES
 * ================================================
 */
/**
 * Parses the .csv files, storing the values in a vector of strings.
 * @param filename File to parse.
 * @return Vector with parsed strings.
 */
void parseCsv(ifstream & filename, vector<string> & parsed);
/**
 * Checks if a certain file is empty.
 * @param path File to evaluate.
 * @return true If empty, false otherwise.
 */
bool ficheiroVazio(const string & path);
/**
 * Creates a file if it is not already existant.
 * @param path File to create.
 */
void criaFicheiro(const string & path);

/*
 * ================================================
 *                STORE INFORMATION
 * ================================================
 */
/**
 * Stores the Empresa's information in the 'Empresa.csv' file.
 * @param e Empresa to save.
 */
void gravaEmpresa(const Company & e);
/**
 * Stores the number of existing Condominios in the 'Condominios.csv' file.
 * @param e Empresa.
 */
void gravaCondominios(const Company & e);
/**
 * Stores all information regarding Tecnicos in the 'Tecnicos.csv' file.
 * @param e Empresa.
 */
void gravaTecnicos(const Company & e);
/**
 * Stores all information regarding Proprietarios in the 'Proprietarios.csv' file.
 * @param e Empresa.
 */
void gravaProprietarios(const Company & e);
/**
 * Stores all information regarding Propriedades in the 'Propriedades.csv' file.
 * @param e Empresa.
 */
void gravaPropriedades(const Company & e);
/**
 * Stores all the information regarding all the external inspections in a file.
 * @param e Company.
 */
void saveExtInspections(const Company & e);
/**
 * Saves all the Reservations information to a file.
 * @param c Company.
 */
void saveReservations(const Company & c);
/**
 * Saves all old condos to file.
 * @param c Company
 */
void saveOldCondos(const Company & c);
/**
 * Saves all the free ids to file.
 * @param c Company.
 */
void saveFreeIDs(const Company & c);
/*
 * ================================================
 *               LOAD INFORMATION
 * ================================================
 */
/**
 * Loads all the Company.
 *
 * @return Company.
 */
Company loadCompany();
/**
 * Loads all condos from 'condos.csv' file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadCondos(Company & c);
/**
 * Loads all old condos from 'OldCondos.csv' file.
 *
 * @param c Company
 * @return true if loaded successfully, false otherwise.
 */
bool loadOldCondos(Company & c);
/**
 * Loads all properties from 'properties.csv' file.
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadProperties(Company & c);
/**
 * Loads all technicians from 'technicians.csv' file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadTechnicians(Company & c);
/**
 * Loads all owners from 'owners.csv' file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadOwners(Company & c);
/**
 * Loads all external inspections from "ExtInspections.csv" file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadExtInspections(Company & c);
/**
 * Loads all reservations from "reservations.csv" file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadReservations(Company & c);
/**
 * Loads all free ids from "FreeIDs.csv" file.
 *
 * @param c Company.
 * @return true if loaded successfully, false otherwise.
 */
bool loadFreeIDs(Company & c);
/*
 * ================================================
 *                     SLOTS
 * ================================================
 */
void parseSlots(vector<bool> & slots_state, const string & slot);
int slotLivre();
bool criaPasta(const string & nome_pasta);

#endif /* FICHEIROS_H_ */

