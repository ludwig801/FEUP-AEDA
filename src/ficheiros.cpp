/*
 * ficheiros.cpp
 *
 *  Created on: 6 de Nov de 2013
 *      Author: Kevin Amorim
 */

#include "ficheiros.h"


void parseCsv(ifstream & filename, vector<string> & parsed) {

	parsed.clear(); /* Clears vector for security purposes. */

	if (!filename) return; /* Return empty parse if file does not exist. */

	string line, value;
	size_t pos;

	// Ignores header line. */
	getline(filename, line);

	while(getline(filename, line)) {

		if(line.size() == 0) break; /* Ignores empty line, if it exists. */

		do {
			pos = line.find(DELIMITER);

			value = line.substr(0, pos);

			line.replace(line.begin(), line.end(), line.substr(pos + 1));

			parsed.push_back(value);

		} while (pos != string::npos);

		parsed.push_back("\n"); /* Parse new line. Works like  tag. */

	}

}

bool ficheiroVazio(const string & path) {
	ifstream file;

	if(!file) return false;

	file.open(path.c_str(), ios::in);
	file.seekg(0, ios::end);
	int length = file.tellg();

	if(length == 0) return true;
	else return false;

}

void criaFicheiro(const string & path)  {

	fstream file(path.c_str(), ios::in);

	/* Verifica se ficheiro já existe. Se não existir, cria. */
	if(!file)
		file.open(path.c_str(), ios::out);

	file.close();

}

void gravaEmpresa(const Company & e) {

	cout << "A gravar empresa..." << endl;

	ofstream file(COMPANY_CSV.c_str(), ios::out);

	/* Escreve info da Empresa. */
	file << e;

	file.close();

}

void gravaCondominios(const Company & e) {

	cout << "A gravar condominios..." << endl;

	ofstream file(CONDOS_CSV.c_str(), ios::out);

	file << CONDOS_HEADER << endl;

	vector<Condo *> condos = e.getCondos();

	// Writes last id of the condos.
	file << condos[0]->getLastID() << endl;

	for(vector<Condo *>::iterator it = condos.begin();
			it != condos.end(); ++it) {
		file << **it << endl;
	}

	file.close();

}

void gravaPropriedades(const Company & e) {

	cout << "A gravar propriedades..." << endl;

	ofstream file(PROPERTIES_CSV.c_str(), ios::out);

	file << PROPERTIES_HEADER << endl;

	vector<Condo *> condominios = e.getCondos();

	for(size_t i = 0; i < condominios.size(); i++) {

		for(size_t j = 0; j < condominios[i]->getPropriedades().size(); j++) {

			/* So that when loading again the properties the total properties number matches the reality. */
			e.getCondos()[i]->decrementTotalProperties();

			file << condominios[i]->getPropriedades()[j];

		}
	}

}

void gravaTecnicos(const Company & e) {

	cout << "A gravar tecnicos..." << endl;

	ofstream file(TECHNICIANS_CSV.c_str(), ios::out);

	file << TECHNICIANS_HEADER << endl;

	if(e.getTechinicians().size() == 0) {
		remove(TECHNICIANS_CSV.c_str());
		return;
	}

	vector<Technician *> tecnicos = e.getTechinicians();

	/* Escreve informação dos Técnicos no ficheiro. */
	for(vector<Technician *>::iterator it = tecnicos.begin();
			it != tecnicos.end(); ++it) {

		file << **it;

	}

	file.close();

}

void gravaProprietarios(const Company & e) {

	cout << "A gravar proprietarios..." << endl;

	ofstream file(OWNERS_CSV.c_str(), ios::out);

	file << OWNERS_HEADER << endl;

	vector<Owner *> proprietarios = e.getOwners();

	for(size_t i = 0; i < proprietarios.size(); i++)
		file << *proprietarios[i] << endl;

}

void saveExtInspections(const Company & e) {

	cout << "A gravar inspeccoes externas..." << endl;

	ofstream file(EXT_INSPECTIONS_CSV.c_str(), ios::out);

	file << EXT_INSPECTIONS_HEADER << endl;

	BSTItrIn<ExtInspection> itr = e.getBSTIteratorIn();

	while(!itr.isAtEnd()) {

		ExtInspection tmp = itr.retrieve();

		file << tmp.getName() << ";" << tmp.getLocalization() << ";" << tmp.getInspectionType()
				<< ";" << tmp.getPrice() << endl;

		itr.advance();

	}

}

void saveReservations(const Company & c) {

	cout << "A gravar reservas do salao de eventos..." << endl;

	ofstream file(RESERVATIONS_CSV.c_str(), ios::out);

	file << RESERVATIONS_HEADER << endl;

	HEAP_SALOON tmp = c.getSaloonReservations();

	while(!tmp.empty()) {
		file << tmp.top().getCondo()->getID() << ";"
				<< tmp.top().getYear() << ";" << tmp.top().getMonth() << ";"
				<< tmp.top().getState() << endl;
		tmp.pop();
	}

}

void saveOldCondos(const Company & c) {

	cout << "A gravar condominios antigos..." << endl;

	ofstream file(OLD_CONDOS_CSV.c_str(), ios::out);

	file << OLD_CONDOS_HEADER << endl;

	HashCondos oldCondos = c.getOldCondosHashTable();

	for(HashCondos::iterator it = oldCondos.begin();
			it != oldCondos.end(); ++it) {
		file << **it << endl;
	}

	file.close();

}

void saveFreeIDs(const Company & c) {

	cout << "A gravar IDs livres..." << endl;

	ofstream file(FREE_IDS_CSV.c_str(), ios::out);

	file << FREE_IDS_HEADER << endl;

	priority_queue<int> free = c.getFreeIDs();

	while(!free.empty()) {
		file << free.top() << endl;
		free.pop();
	}

	file.close();

}

Company loadCompany() {

	ifstream file (COMPANY_CSV.c_str());

	bool isDefault = false; /* Verifica se ja estamos a tratar dos valores default da periodicidade. */

	vector<string> members; parseCsv(file, members);

	vector<string> final;

	string name, balance_str, month_str, year_str, confirmation_str;

	map<string, pair<size_t, size_t> > inspeccoes;
	map<string, size_t> default_values;

	if (members.size() == 0) {

		cout << "Ficheiro " << COMPANY_CSV << " vazio ou inexistente." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		throw FileError(COMPANY_CSV);

	}

	for(size_t i = 0; i < members.size(); i++) {

		final.push_back(members[i]);

		/* Dados da Empresa */
		if(members[i] == "\n" && (i == 5)) {

			name = members[0];
			balance_str = members[1];
			month_str = members[2];
			year_str = members[3];
			confirmation_str = members[4];

			final.clear();

		} else if (!isDefault && (members[i] == "\n")) {

			inspeccoes[final[0]] = make_pair(atoi(final[1].c_str()), atoi(final[2].c_str()));
			final.clear();

		} else if ((final[0] == "default")) {

			isDefault = true;
			i++;
			final.clear();

		} else if(isDefault && (members[i] == "\n")) {

			default_values[final[0]] = atoi(final[1].c_str());

			final.clear();

		}

	}

	// Verifications
	if(!IsStringName(name)) name = "default";
	if(!IsStringNumber(balance_str)) balance_str = "0";
	if(!IsStringNumber(month_str)) month_str = "1";
	if(!IsStringNumber(year_str)) year_str = "1";
	if(!IsStringNumber(confirmation_str)) confirmation_str = "1";


	size_t balance = atoi(balance_str.c_str());
	size_t month = atoi(month_str.c_str());
	size_t year = atoi(year_str.c_str());
	int confirmation = atoi(confirmation_str.c_str());

	Company e(name, balance, month, year, inspeccoes, default_values, confirmation);



	if (!loadOwners(e)) throw FileError(OWNERS_CSV);

	if (!loadCondos(e)) throw FileError(CONDOS_CSV);

	if(!loadOldCondos(e)) throw FileError(OLD_CONDOS_CSV);

	if(!loadFreeIDs(e)) throw FileError(FREE_IDS_CSV);

	if (!loadProperties(e)) throw FileError(PROPERTIES_CSV);

	if(!loadTechnicians(e)) throw FileError(TECHNICIANS_CSV);

	if (!loadExtInspections(e)) throw FileError(EXT_INSPECTIONS_CSV);

	if (!loadReservations(e)) throw FileError(RESERVATIONS_CSV);

	return e;
}

bool loadCondos(Company & c) {

	ifstream file(CONDOS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	vector<string> members;

	size_t NUM_MEMBERS = 3; /* Numbers of values that each line should contain. (ERROR CHECK). */

	if(values.size() == 0) {

		file.close();

		return true;

	}

	int line = 1, lastID = -1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(line == 2) {

			if(IsStringNumber(members[0]))
				lastID = atoi(members[0].c_str());

			else if(members[0] == "-1") {

				file.close();

				return true;

			}

			else {

				error = true;
				break;

			}

			line++;
			members.clear();
			continue;

		}

		line++;

		if(members.size() == NUM_MEMBERS &&
				IsStringNumber(members[0]) &&
				IsStringNumber(members[1]) &&
				IsStringNumber(members[2])) {

			int id = atoi(members[0].c_str());
			int localization = atoi(members[1].c_str());
			size_t total_properties = atoi(members[2].c_str());

			c.createCondo(id, localization, total_properties);

			if (c.getCondos().size() != 0) c.getCondos()[0]->incrementLastID();

		} else {

			error = true;
			break;

		}

		members.clear();

	}

	if (error) {

		/* File line was corrupted. */
		cout << "Ficheiro " << CONDOS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();

		return false;

	}

	if (c.getCondos().size() != 0) {

		/* Matches last ID. */
		while(c.getCondos()[0]->getLastID() < lastID) {
			c.getCondos()[0]->incrementLastID();
		}

	}


	file.close();
	return true;

}

bool loadOldCondos(Company & c) {

	ifstream file(OLD_CONDOS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	vector<string> members;

	size_t NUM_MEMBERS = 3; /* Numbers of values that each line should contain. (ERROR CHECK). */

	if(values.size() == 0) {

		file.close();

		return true;

	}

	int line = 1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(members.size() == NUM_MEMBERS &&
				IsStringNumber(members[0]) &&
				IsStringNumber(members[1]) &&
				IsStringNumber(members[2])) {

			int id = atoi(members[0].c_str());
			int localization = atoi(members[1].c_str());
			size_t total_properties = atoi(members[2].c_str());

			Condo * co = new Condo(id, localization, total_properties);

			c.addCondoToOldCondos(*co);

		} else {

			error = true;
			break;

		}

		members.clear();

	}

	if (error) {

		/* File line was corrupted. */
		cout << "Ficheiro " << CONDOS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();

		return false;

	}

	file.close();
	return true;

}

bool loadProperties(Company & c) {

	ifstream file(PROPERTIES_CSV.c_str());

	vector<string> values; parseCsv(file, values);		/*< All strings in the file. */
	vector<string> members;
	vector<Property *> propriedades;					/*< Temporary vector of properties. */

	size_t id_condominio, area, andar, tipo_contrato, index_propriedade,
		index_proprietario, meses_restantes;
	string tipo_propriedade, nome_proprietario;

	string tipos_propriedade[] 	= { "residencia" , "escritorio" , "loja" };
	string tipos_contrato[] 	= { "mensal" , "semestral" , "anual", "nenhum" };



	if(values.size() == 0) {

		file.close();
		return true;

	}

	/* There are no condos to create the properties. */
	if(c.getCondos().size() == 0) {

		cout << endl << "Nao existem condominios para se poderem criar as propriedades." << endl
				<< "Por favor, corrija o ficheiro: " << CONDOS_CSV << " e tente novamente." << endl << endl;

		file.close();

		return false;

	}

	int line = 1;			/* Actual file line. */
	bool error = false; 	/* Error flag. */
	bool existe = false; 	/* Owner exists flag. */
	for(unsigned int i = 0; i < values.size(); i++) {

		members.push_back(values[i]);

		if(values[i] == "\n") {

			line++;

			if(IsStringNumber(members[0])) id_condominio = atoi(members[0].c_str());
			else {
				error = true;
				break;
			}

			if((members[1] == tipos_propriedade[0]) ||
					members[1] == tipos_propriedade[1] ||
					members[1] == tipos_propriedade[2]) tipo_propriedade = members[1];
			else {
				error = true;
				break;
			}

			if(IsStringNumber(members[2])) area = atoi(members[2].c_str());
			else {
				error = true;
				break;
			}
			if(IsStringNumber(members[3])) andar = atoi(members[3].c_str());
			else {
				error = true;
				break;
			}
			if(IsStringNumber(members[6])) meses_restantes = atoi(members[6].c_str());
			else {
				error = true;
				break;
			}

			/*
			 * TIPO CONTRATO:
			 * 			0 - Mensal
			 * 			1 - Semestral
			 * 			2 - Anual
			 *
			 */
			if (members[5] == tipos_contrato[0]) tipo_contrato = 0;
			else if (members[5] == tipos_contrato[1]) tipo_contrato = 1;
			else if (members[5] == tipos_contrato[2]) tipo_contrato = 2;
			else if (members[5] == tipos_contrato[3]) tipo_contrato = 3;
			else {
				error = true;
				break;
			}

			/*
			 * TIPO PROPRIEDADE:
			 * 			0 - Residência
			 * 			1 - Escritório
			 * 			2 - Loja
			 *
			 */

			if(tipo_propriedade == tipos_propriedade[0]) c.addProperty(id_condominio, area, andar, 0);
			else if(tipo_propriedade == tipos_propriedade[1]) c.addProperty(id_condominio, area, andar, 1);
			else if(tipo_propriedade == tipos_propriedade[2]) c.addProperty(id_condominio, area, andar, 2);
			else {
				error = true;
				break;
			}

			if(IsStringName(members[4]) || members[4] == "-1") nome_proprietario = members[4];
			else {
				error = true;
				break;
			}

			if(nome_proprietario != "-1") {

				/* Verifica se nome do proprietário existe */
				for(size_t i = 0; i < c.getOwners().size(); i++) {

					if(c.getOwners()[i]->getNome() == nome_proprietario) {
						existe = true;
						break;
					}

				}

				if(existe) {

					index_propriedade = c.getCondos()[id_condominio]->getPropriedades().size() - 1;
					if(index_propriedade < 0) {
						error = true;
						break;
					}

					index_proprietario = c.searchOwner(nome_proprietario);
					if(index_proprietario < 0) {
						error = true;
						break;
					}

					c.createContract(id_condominio, index_propriedade, index_proprietario, tipo_contrato);
					c.setRemainingMonths(id_condominio, index_propriedade, meses_restantes);

				}

			}

			existe = false;
			/* Cleans members vector. */
			members.clear();
		}
	}


	if(error) {

		cout << "Ficheiro " << PROPERTIES_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();

		return false;

	}


	file.close();
	return true;
}

bool loadTechnicians(Company & c) {

	ifstream file(TECHNICIANS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	if(values.size() == 0) {

		file.close();
		return true;

	}

	vector<string> members;

	size_t NUM_MEMBERS = 4; /* Numbers of values that each line should contain. (ERROR CHECK). */

	int line = 1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(members.size() == NUM_MEMBERS) {

			if ( (!IsStringName(members[0])) ||
					(!IsStringProfession(members[1])) ||
					(!IsStringNumber(members[2])) )
			{

				error = true;
				break;

			}

			c.createTechnician(members[0], members[1], atoi(members[2].c_str()));
			members.clear();

		} else {

			error = true;
			break;

		}

	}


	if (error) {

		cout << "Ficheiro " << TECHNICIANS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();

		return false;

	}

	file.close();

	return true;

}

bool loadOwners(Company & c) {

	ifstream file(OWNERS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	if(values.size() == 0) {

		file.close();
		return true;

	}

	string user_name;

	int line = 1;
	for(size_t i = 0; i < values.size(); i++) {

		user_name = values[i];

		line++;

		if(user_name.compare("\n") == 0) continue;

		// Validates parsed username.
		if(IsStringName(user_name)) {

			c.addOwner(values[i]);

		} else {

			cout << "Ficheiro " << OWNERS_CSV << " corrompido na linha: " << line << "." << endl
					<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

			file.close();
			return false;

		}

	}

	file.close();

	return true;

}

bool loadExtInspections(Company & c) {

	ifstream file(EXT_INSPECTIONS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	if(values.size() == 0) {

		file.close();
		return true;

	}

	vector<string> members;

	size_t NUM_MEMBERS = 4; /* Numbers of values that each line should contain. (ERROR CHECK). */

	int line = 1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(members.size() == NUM_MEMBERS) {

			if(IsStringName(members[0]) &&
					IsStringNumber(members[1]) &&
					IsStringProfession(members[2]) &&
					IsStringNumber(members[3])) {

				ExtInspection e(members[0], atoi(members[1].c_str()), members[2], atoi(members[3].c_str()));
				c.addExtInspectionToBST(e);

			} else {

				error = true;
				break;

			}

			members.clear();

		} else {

			error = true;
			break;

		}

	}

	if (error) {

		cout << "Ficheiro " << EXT_INSPECTIONS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();
		return false;

	}

	file.close();
	return true;

}

bool loadReservations(Company & c) {

	ifstream file(RESERVATIONS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	if(values.size() == 0) {

		file.close();
		return true;

	}

	vector<string> members;

	size_t NUM_MEMBERS = 4; /* Numbers of values that each line should contain. (ERROR CHECK). */

	int line = 1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(members.size() == NUM_MEMBERS) {

			if(IsStringNumber(members[0]) &&
					IsStringNumber(members[1]) &&
					IsStringNumber(members[2]) ) {

				int condo_id = atoi(members[0].c_str());
				int year = atoi(members[1].c_str());
				int month = atoi(members[2].c_str());
				bool state = atoi(members[3].c_str());

				try {

					Condo * condo = c.searchCondoByID(condo_id);

					Reservation r(condo, month, year, state);

					c.addReservation(r);

				} catch (Company_Error<string, int> & e) {

					cout << "Ficheiro " << RESERVATIONS_CSV << " corrompido na linha: " << line << "." << endl
							<< "Por favor, corrija o ficheiro e tente novamente." << endl
							<< "Erro retornado: " << endl
							<< e.error << " ID: " << e.value << endl << endl;

					file.close();
					return false;

				}


			} else {

				/* Some line was corrupted. */
				error = true;
				break;

			}

			members.clear();

		} else {

			/* Some line was corrupted. */
			error = true;
			break;

		}

	}

	if (error) {

		cout << "Ficheiro " << RESERVATIONS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();
		return false;

	}

	file.close();
	return true;

}

bool loadFreeIDs(Company & c) {

	ifstream file(FREE_IDS_CSV.c_str());

	vector<string> values; parseCsv(file, values);

	if(values.size() == 0) {

		file.close();
		return true;

	}

	vector<string> members;

	size_t NUM_MEMBERS = 1; /* Numbers of values that each line should contain. (ERROR CHECK). */

	int line = 1;
	bool error = false; /* Error flag. */
	for(size_t i = 0; i < values.size(); i++) {

		if(values[i] != "\n") {
			members.push_back(values[i]);
			continue;
		}

		line++;

		if(members.size() == NUM_MEMBERS) {

			if(IsStringNumber(members[0])) {

				int condo_id = atoi(members[0].c_str());

				c.insertFreeID(condo_id);

			} else {

				/* Some line was corrupted. */
				error = true;
				break;

			}

			members.clear();

		} else {

			/* Some line was corrupted. */
			error = true;
			break;

		}

	}

	if (error) {

		cout << "Ficheiro " << FREE_IDS_CSV << " corrompido na linha: " << line << "." << endl
				<< "Por favor, corrija o ficheiro e tente novamente." << endl << endl;

		file.close();
		return false;

	}

	file.close();

	return true;

}
