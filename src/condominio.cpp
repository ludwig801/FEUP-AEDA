#include "condominio.h"
#include "empresa.h"

/*
* ==================================
*          CONSTRUCTORS
* ==================================
*/
Condo::Condo() : id(++last_id), localization(0), total_properties(0) {}

Condo::Condo(int & id) : id(id), localization(0), total_properties(0) {}

Condo::Condo(int & localization, size_t & total_properties) : id(++last_id), localization(localization), total_properties(total_properties) {}

Condo::Condo(int & id, int & localization, size_t & total_properties) : id(id), localization(localization), total_properties(total_properties) {}

int Condo::last_id = -1;
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *             DESTRUCTOR
 * ==================================
 */
Condo::~Condo() {

	for (vector<Property *>::iterator it = this->propriedades.begin();
			it != this->propriedades.end(); ++it) {
		delete *it;
	}

}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           MEMBER GETTERS
 * ==================================
 */
int Condo::getID() const {
	return id;
}

int Condo::getLastID() {
	return last_id;
}

int Condo::getLocalization() const {
	return localization;
}

size_t Condo::getTotalProperties() const {
	return total_properties;
}

vector<Property *> Condo::getPropriedades() const {
	return propriedades;
}

size_t Condo::getTotalValue() const {

	size_t value = 0;
	for(vector<Property *>::const_iterator it = propriedades.begin();
			it != propriedades.end(); ++it) {

		value += (*it)->getValue();

	}

	return value;

}

size_t Condo::getNumPropriedadesLivres() {

	size_t numPropsLivres = 0;
	for (size_t i = 0; i < this->propriedades.size(); i++) {

		if(!(this->propriedades[i]->existsOwner()))
			numPropsLivres++;

	}

	return numPropsLivres;
}

map<pair<int, int>, int> Condo::getProfit() const {
	return profit;
}

map<pair<int, int>, int> Condo::getExpenses() const {
	return expenses;
}

map<pair<int, int>, vector<pair<int, int> > > Condo::getTechServices() const {
	return techServices;
}

map<pair<int, int>, int> Condo::getCommonSpacesExpenses() const {
	return commonSpacesExpenses;
}

map<pair<int, int>, vector<pair<string, int> > > Condo::getExtInspectionsCalls() const {
	return extInspectionsCalls;
}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           MEMBER SETTERS
 * ==================================
 */
void Condo::setLocalization(int & localization) {
	this->localization = localization;
}

void Condo::setTotalProperites(size_t & total_properties) {
	this->total_properties = total_properties;
}

void Condo::addProperty(const size_t & index, const size_t & area, const size_t & floor, const size_t & type) {

	switch(type) {
	case RESIDENCE:
		this->propriedades.push_back(new Residence(index, area, floor));
		break;
	case STORE:
		this->propriedades.push_back(new Store(index, area, floor));
		break;
	case OFFICE:
		this->propriedades.push_back(new Office(index, area, floor));
		break;
	}

	total_properties++;

}

void Condo::eliminaPropriedade(const size_t & index) {
	this->propriedades.erase(this->propriedades.begin() + index);
}

void Condo::eliminaTodasPropriedades() {
	this->propriedades.clear();
}

void Condo::eliminaContratoPropriedade(const size_t & index) {
	this->propriedades[index]->removeContract();
}

void Condo::criaContrato(const size_t & index, const size_t & typeContrato, Owner * p) {
	this->propriedades[index]->createContract(typeContrato, p);
}

void Condo::decrementaMesesRestantes() {

	for(vector<Property *>::iterator it = this->propriedades.begin();
			it != this->propriedades.end(); ++it) {

		(*it)->decrementMoths();

	}

}

void Condo::resetMesesRestantes(const size_t & index) {
	this->propriedades[index]->resetMonths();
}

void Condo::setMesesRestantes(const size_t & index, const size_t & meses) {
	this->propriedades[index]->setRemainingMonths(meses);
}

void Condo::incrementTotalProperties() {
	this->total_properties++;
}

void Condo::decrementTotalProperties() {
	this->total_properties--;
}

void Condo::incrementLastID() {
	last_id++;
}

void Condo::decrementLastID() {
	last_id--;
}

void Condo::insertProfit(const int & year, const int & month, const int & value) {
	pair<int, int> date = make_pair(year, month);
	profit[date] = value;
}

void Condo::insertExpenses(const int & year, const int & month, const int & value) {
	pair<int, int> date = make_pair(year, month);
	expenses[date] = value;
}

void Condo::insertExtInspectionCall(const int & year, const int & month, const string & name, const int & cost) {
	pair<int, int> date = make_pair(year, month);
	pair<string, int> value = make_pair(name, cost);
	extInspectionsCalls[date].push_back(value);
}

void Condo::insertTechService(const int & year, const int & month, const int & service, const int & cost) {
	pair<int, int> date = make_pair(year, month);
	pair<int, int> value = make_pair(service, cost);

	techServices[date].push_back(value);

}

void Condo::insertCommonSpacesExpenses(const int & year, const int & month, const int & expenses) {
	pair<int, int> date = make_pair(year, month);

	commonSpacesExpenses[date] = expenses;
}

void Condo::clearsFinancialLog() {
	profit.clear();
	expenses.clear();
	techServices.clear();
	commonSpacesExpenses.clear();
}

void Condo::writeCondoProfit(ofstream & file, const int & year, const int & month) {
	pair<int, int> date = make_pair(year, month);
	file << " Lucro: " << profit[date] << endl;
}

void Condo::writeCondoExpenses(ofstream & file, const int & year, const int & month) {
	pair<int, int> date = make_pair(year, month);
	file << " Despesa: " << expenses[date] << endl;
}

void Condo::writeServices(ofstream & file, const int & year, const int & month) {

	pair<int, int> date = make_pair(year, month);

	if(techServices.find(date) == techServices.end()) return;

	for(vector<pair<int, int> >::const_iterator it = techServices[date].begin();
			it != techServices[date].end(); ++it) {

		if( (*it).first > 5 ) continue;

		if( (*it).second >= 0) {
			file << "Condominio " << id << " requere " << professions_list[(*it).first]
			      << ", custo: " << (*it).second << endl;
		} else {
			file << "Condominio " << id << " requere " << professions_list[(*it).first]
			      << ", NAO DISPONIVEL." << endl;
		}

	}

	techServices.erase(date);

}

void Condo::writeCommonSpacesExpenses(ofstream & file, const int & year, const int & month) {

	pair<int, int> date = make_pair(year, month);

	if(commonSpacesExpenses.find(date) == commonSpacesExpenses.end()) return;

	file << " Espacos Comuns: " << commonSpacesExpenses[date] << endl;

	commonSpacesExpenses.erase(date);

}

void Condo::writeExtInspectionsCalls(ofstream & file, const int & year, const int & month) {

	pair<int, int> date = make_pair(year, month);

	if(extInspectionsCalls.find(date) == extInspectionsCalls.end() ) return;

	for(vector<pair<string, int> >::const_iterator it = extInspectionsCalls[date].begin();
			it != extInspectionsCalls[date].end(); ++it) {
		file << " Foi chamada a inspecao externa "
				<< it->first << " com um custo de " << it->second << endl;
	}

	extInspectionsCalls.erase(date);
}
/*
 * ==================================
 * ==================================
 */

ExtInspection * Condo::searchBestExtInspection(const Company & c, const string & type, bool byPrice) const {


	if(c.isExtInspectionsEmpty()) throw ExtInspection_Error(); /* Arvore vazia. */

	vector<BSTItrIn<ExtInspection> > filtered;
	BSTItrIn<ExtInspection> bestMatch = c.getBSTIteratorIn();

	BSTItrIn<ExtInspection> itr = c.getBSTIteratorIn();

	while(!itr.isAtEnd()) {

		if(type == itr.retrieve().getInspectionType()) filtered.push_back(itr);
		itr.advance();

	}

	// Returns the external company closest to the condo.
	for(size_t i = 0; i < filtered.size(); i++) {

		if(bestMatch.retrieve().getInspectionType() != type) {
			bestMatch = filtered[i];
			continue;
		}

		if(byPrice) {

			if( bestMatch.retrieve().getPrice() > filtered[i].retrieve().getPrice() )
				if(filtered[i].retrieve().getInspectionType() == type)
					bestMatch = filtered[i];

		} else {

			if( abs(localization - filtered[i].retrieve().getLocalization()) <
					abs(localization - bestMatch.retrieve().getLocalization()) )
				if(filtered[i].retrieve().getInspectionType() == type)
					bestMatch = filtered[i];

		}

	}

	if(bestMatch.retrieve().getInspectionType() != type) throw ExtInspection_Error();

	return &bestMatch.retrieve();

}

bool Condo::operator ==(const Condo & co) const {

	return ( id == co.getID() );

}

ostream & operator<<(ostream & o, const Condo & c) {

	o << c.id << ";" << c.localization << ";" << c.total_properties;

	return o;

}
