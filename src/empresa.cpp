#include "empresa.h"

Company::Company() : name("default"), balance(0), month(1), year(1), confirmationLimit(1), startingDate(make_pair(year, month)),
	extInspectionsBST(ExtInspection()), MAX_VARIATION(60) { }

Company::Company(string name, long int balance, int month, int year,
		map<string, pair<size_t, size_t> > inspeccoes, map<string, size_t> periodicidade_default, int confirmationLimit) :

		name(name), balance(balance), month(month), year(year),
		confirmationLimit(confirmationLimit),
		startingDate(make_pair(year, month)),
		inspections(inspeccoes), periodicity_default(periodicidade_default),
		extInspectionsBST(ExtInspection()), MAX_VARIATION(60) { }
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           DESTRUCTOR
 * ==================================
 */
Company::~Company() { }
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           MEMBER GETTERS
 * ==================================
 */
string Company::getName() const {
	return this->name;
}

long int Company::getBalance() const {
	return this->balance;
}

int Company::getMonth() const {
	return this->month;
}

int Company::getYear() const {
	return this->year;
}

pair<int, int> Company::getInitialDate() const {
	return startingDate;
}

vector<Condo *> Company::getCondos() const {
	return this->condos;
}

vector<Technician *> Company::getTechinicians() const {
	return this->technicians;
}

vector<Owner *> Company::getOwners() const {
	return this->owners;
}

map<string, pair<size_t, size_t> > Company::getInspections() const {
	return this->inspections;
}

map<string, size_t> Company::getPeriodicityDefault() const {
	return this->periodicity_default;
}

map<pair<int, int>, int> Company::getTotalWages() const {
	return total_wages;
}

map<pair<int, int>, vector<pair<string, int> > >  Company::getTotalInspections() const {
	return total_inspections;
}

int Company::getConfirmationLimit() const {
	return confirmationLimit;
}

map<pair<int, int>, pair<int, bool> > Company::getEvents() const {
	return events;
}

priority_queue<int> Company::getFreeIDs() const {
	return free_condo_ids;
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
void Company::setName(const string nome) {
	this->name = nome;
}

void Company::setBalance(const size_t saldo) {
	this->balance = saldo;
}

void Company::setMonth(const int & mes) {
	this->month = mes;
}

void Company::setYear(const int & ano) {
	this->year = ano;
}

void Company::incrementMonth() {

	if(this->month < 12) {

		this->month++;

	} else {

		this->month = 1;
		this->year++;

	}
}

void Company::incrementYear() {
	this->year++;
}

void Company::setNameTechnician(const size_t & index, const string & nome) {
	this->technicians[index]->setNome(nome);
}

void Company::setSalaryTechnician(const size_t & index, const size_t & salario) {
	this->technicians[index]->setSalario(salario);
}

void Company::setProfessionTechnician(const size_t & index, const string & profissao) {
	this->technicians[index]->setProfissao(profissao);
}

void Company::setNameOwner(const size_t & index, const string & nome) {
	this->owners[index]->setNome(nome);
}

void Company::setInspectionPeriodicity(const string & key, const size_t & periodicidade) {
	this->inspections.find(key)->second.first = periodicidade;
}

void Company::setInspectionCost(const string & key, const size_t & custo) {
	this->inspections.find(key)->second.second = custo;
}

void Company::decrementInspections() {

	for(map<string, pair<size_t, size_t> >::iterator it = this->inspections.begin();
			it != this->inspections.end(); ++it) {

		if(it->second.first == 0) {
			it->second.first = this->periodicity_default.find(it->first)->second;
		} else {
			it->second.first--;
		}

	}
}

void Company::setRemainingMonths(const size_t & index, const size_t & id, const size_t & meses) {
	this->condos[index]->setMesesRestantes(id, meses);
}

void Company::insertTotalWages(const int & year, const int & month, const int & wages) {
	pair<int, int> date = make_pair(year, month);

	total_wages[date] = wages;
}

void Company::insertTotalInspections(const int & year, const int & month, const string & type, const int & cost) {
	pair<int, int> date = make_pair(year, month);

	pair<string, int> value = make_pair(type, cost);

	total_inspections[date].push_back(value);
}

void Company::setConfirmationLimit(const int & confirmationLimit) {
	this->confirmationLimit = confirmationLimit;
}

void Company::insertEvent(const int & year, const int & month, const int & condo_id, const bool & realized) {
	pair<int, int> date = make_pair(year, month);
	pair<int, bool> value = make_pair(condo_id, realized);

	events[date] = value;
}

void Company::insertFreeID(const int & condo_id) {
	free_condo_ids.push(condo_id);
}

void Company::removeFreeID() {
	free_condo_ids.pop();
}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           CONDOMINIOS
 * ==================================
 */
void Company::createCondo() {

	if( free_condo_ids.size() != 0) {
		int id = free_condo_ids.top();
		free_condo_ids.pop();
		this->condos.push_back(new Condo(id));
	} else {
		this->condos.push_back(new Condo());
	}

}

void Company::createCondo(int localization, size_t total_properties) {
	if( free_condo_ids.size() != 0) {
		int id = free_condo_ids.top();
		free_condo_ids.pop();
		this->condos.push_back(new Condo(id, localization, total_properties));
	} else {
		this->condos.push_back(new Condo(localization, total_properties));
	}
}

void Company::createCondo(int & id, int & localization, size_t & total_properties) {
	this->condos.push_back(new Condo(id, localization, total_properties));
}

void Company::receiveParcels() {

	if(this->owners.size() == 0 || this->condos.size() == 0) return;

	size_t total_recebido = 0, total_condominio = 0;

	for(size_t i = 0; i < this->condos.size(); i++) { /* Verifica condomínio. */

		total_condominio = 0;

		for(size_t j = 0; j < this->condos[i]->getPropriedades().size(); j++) { /* Verifica propriedade. */

			/* Verifica se propriedade tem proprietário. Em caso afirmativo recebe a respectiva parcela. */
			if(this->condos[i]->getPropriedades()[j]->existsOwner()) {

				if(this->condos[i]->getPropriedades()[j]->getRemainingMonths() == 0) {

					total_condominio += this->condos[i]->getPropriedades()[j]->getValue();

					/* Reset aos meses restantes */
					this->condos[i]->resetMesesRestantes(j);

				}

			}

		}

		total_recebido += total_condominio;

		condos[i]->insertProfit(year, month, total_recebido);
		this->commonSpacesExpenses(i);

	}

	this->balance += total_recebido;


}

void Company::addProperty(size_t index, size_t area, size_t floor, size_t type) {
	if(index >= this->condos.size()) {
		return;
	} else {
		this->condos[index]->addProperty(index, area, floor, type);
	}
}

void Company::decrementRemainingMonths() {

	for(vector<Condo *>::iterator it = this->condos.begin();
			it != this->condos.end(); ++it) {

		(*it)->decrementaMesesRestantes();

	}
}

bool Company::isLocalizationValid(const int & localization) const {

	for(vector<Condo *>::const_iterator it = condos.begin();
			it != condos.end(); ++it) {

		if( (*it)->getLocalization() == localization ) return false;

	}

	return true;

}

Condo * Company::searchCondoByID(const int & id) const {

	for(vector<Condo *>::const_iterator it = condos.begin();
			it != condos.end(); ++it) {
		if((*it)->getID() == id) return *it;
	}

	// Not found
	throw Company_Error<string, int>("Condo not found.", id);
}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *             TECNICOS
 * ==================================
 */
void Company::createTechnician(string nome, string profissao, size_t salario) {
	this->technicians.push_back(new Technician(nome, profissao, salario));
}

bool Company::technicianExists(string nome) const {

	for(vector<Technician *>::const_iterator it = this->technicians.begin();
			it != this->technicians.end(); ++it) {

		if ((*it)->getNome() == nome) return true;

	}

	return false;

}

Technician * Company::searchTechnician(string nome) const {

	for(vector<Technician *>::const_iterator it = this->technicians.begin();
			it != this->technicians.end(); ++it) {

		if((*it)->getNome() == nome) return (*it);

	}

	throw(Company_Error<string, int>("Tecnico nao existente.", -1));

}

void Company::payTechnicians() {

	size_t total_pago = 0;

	 /* If there are any techs. */
	if(technicians.size() != 0) {

		for(vector<Technician *>::iterator it = this->technicians.begin();
				it != this->technicians.end(); ++it) {

			total_pago += (*it)->getSalario();

		}

	}

	balance -= total_pago;

	insertTotalWages(year, month, total_pago);

}

bool Company::callTechnician(const int & profissao_index, const size_t & index) {

	bool found = false;

	string type = professions_list[profissao_index];

	for(size_t i = 0; i < this->technicians.size(); i++) {

		if((this->technicians[i]->getProfissao() == type) && (this->technicians[i]->getDisponibilidade())) {
			found = true;
			this->technicians[i]->setDisponibilidade(); /* Tecnico passa a nao estar disponivel. */
			break;
		}

	}

	Condo * c = searchCondoByID(index);
	if(found) {
		c->insertTechService(year, month, profissao_index, inspections.find(type)->second.second);
		this->balance -= this->inspections.find(type)->second.second;
	} else {
		c->insertTechService(year, month, profissao_index, -1);
	}

	return found;

}

void Company::setTechniciansAvailable() {

	for(vector<Technician *>::iterator it = this->technicians.begin();
			it != this->technicians.end(); ++it) {

		if(!(*it)->getDisponibilidade()) (*it)->setDisponibilidade();

	}

}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *           PROPRIETARIOS
 * ==================================
 */
void Company::addOwner(string nome) {
	this->owners.push_back(new Owner(nome));
}

int Company::searchOwner(string nome) const {

	for(size_t i = 0; i < this->owners.size(); i++) {

		if (this->owners[i]->getNome() == nome) return i;

	}

	return -1;

}

Owner * Company::getOwner(string nome) {

	for(size_t i = 0; i < this->owners.size(); i++) {

		if ( this->owners[i]->getNome() == nome ) {

			return this->owners[i];

		}

	}

	throw(Company_Error<string, int>("Proprietario nao existente.", -1));

}

void Company::createContract(const size_t & index, const size_t & indexPropriedade, const size_t & indexProprietario,
		const size_t & type) {

	Owner * p = this->owners[indexProprietario];

	this->condos[index]->criaContrato(indexPropriedade, type, p);

}

/*
 * ==================================
 *              REMOVE
 * ==================================
 */
void Company::removeCondo(const int & condo_id) {

	try {

		Condo * toAdd = searchCondoByID(condo_id);

		removePropertiesFromOwner(condo_id);
		removeAllReservationsFromCondo(condo_id);

		addCondoToOldCondos(*toAdd);

		toAdd->~Condo(); // Check if we really need that.

		for(vector<Condo *>::iterator it = condos.begin();
					it != condos.end(); ++it) {

				if( (*it)->getID() == condo_id ) {
					condos.erase(it);
					break;
				}

		}

	} catch (Company_Error<string, int> & e) {

		cout << e.error << " ID: " << e.value << endl;
		waitForUser();
		return;

	}


}

void Company::removeProperty(const size_t & index, const size_t & indexPropriedade) {

	/* Elimina propriedade de um proprietario. */
	for(size_t i = 0; i < this->owners.size(); i++) {

		for(size_t j = 0; j < this->owners[i]->getPropriedades().size(); j++) {

			if((this->owners[i]->getPropriedades()[j]->getID_Condo() == index) &&
					(this->owners[i]->getPropriedades()[j]->getID() == indexPropriedade)) {

				this->owners[i]->eliminaPropriedade(this->owners[i]->getPropriedades()[j]->getID());
				break;

			}

		}

	}

	/* Elimina propriedade do condominio. */
	this->condos[index]->eliminaPropriedade(indexPropriedade);

}

void Company::removePropertyContract(const size_t & index, const size_t & indexPropriedade) {

	this->condos[index]->eliminaContratoPropriedade(indexPropriedade);

}

void Company::removeOwner(const size_t & index) {

	this->owners.erase(this->owners.begin() + index);

}

void Company::removeTechnician(const size_t & index) {

	this->technicians.erase(this->technicians.begin() + index);

}

void Company::removeContracts(size_t & index) {
	this->owners[index]->eliminaTodasPropriedades();
}

void Company::removeAllPropertiesFromCondo(Condo * c) {

	this->removePropertiesFromOwner(c->getID());
	c->eliminaTodasPropriedades();

}

void Company::removePropertiesFromOwner(const int & condo_id) {

	for(size_t i = 0; i < this->owners.size(); i++) {

		this->owners[i]->eliminaPropriedadesDeCondominio(condo_id);

	}

}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *            SIMULATION
 * ==================================
 */
void Company::simulate(const size_t & number) {

	size_t meses_decorridos = 0;

	while(meses_decorridos < number) {

		this->receiveParcels();
		this->payTechnicians();
		this->makeInspections();

		this->randomEvents();

		pair<Reservation, bool> res = this->validateReservations();
		if(!res.second) {
			if(confirmReservation(res.first)) {
				bool state = true;
				Reservation r = saloon.top();
				r.setState(state);
				saloon.pop(); saloon.push(r);
			}
		}

		this->prepareMonth();

		meses_decorridos++;

	}

}

void Company::prepareMonth() {

	this->incrementMonth();

	/* Decrementa todos os meses restantes */
	this->decrementRemainingMonths();

	/* Decrementa meses para próximas inspecções. */
	this->decrementInspections();

}

void Company::makeInspections() {

	size_t total_gasto = 0;

	if(this->inspections.size() != 0) {

		for(map<string, pair<size_t, size_t> >::iterator it = this->inspections.begin();
				it != this->inspections.end(); ++it) {

			if(it->second.first == 0) { /* Realiza inspeccao */

				int cost = it->second.second * condos.size();

				insertTotalInspections(year, month, it->first, cost);

				total_gasto += cost;

			}

		}

	}

	this->balance -= total_gasto;
}

void Company::writeMonth(ostream & file, const int & month) {

	if (!file) return;

	string meses[] = { "JANEIRO", "FEVEREIRO", "MARCO", "ABRIL",
			"MAIO", "JUNHO", "JULHO", "AGOSTO", "SETEMBRO",
			"OUTUBRO", "NOVEMBRO", "DEZEMBRO" };

	int i = month - 1;

	if( (i > 11) || (i < 0) ) return;

	file << "\n\n ============================== \n";

	file << ":: " << meses[i] << endl;

	file << " ============================== \n";

}

void Company::commonSpacesExpenses(const size_t & index) {

	size_t total_gasto = 0;

	/* Vamos assumir que quantas mais propriedades um condominio, mais cara a despesa. */

	total_gasto += 40 * this->condos[index]->getPropriedades().size();

	total_gasto += (rand() % 15 + 1) * this->condos[index]->getPropriedades().size();

	this->condos[index]->insertCommonSpacesExpenses(year, month, total_gasto);

	this->balance -= total_gasto;

}

void Company::callTechnicianRandomly(const size_t & index) {

	int random = (rand() % 6);

	this->callTechnician(random, index);

}

void Company::randomEvents() {

	int random;

	for(size_t i = 0; i < this->condos.size(); i++) {

		for(size_t j = 0; j < 4; j++) { /* 21 = media dos dias uteis existentes num mes. */

			random = (rand() % (this->condos[i]->getPropriedades().size()/2 + 1));

			while(random > 0) {

				this->callTechnicianRandomly(i);

				random--;

			}

			this->setTechniciansAvailable();

		}

	}
}

void Company::saveLog() {

	cout << "A gravar relatorio financeiro..." << endl;

	int yearf = startingDate.first;
	int monthf = startingDate.second;
	int breakMonth;

	while(yearf <= (int) year) {

		string caminho_ficheiro = criaNomeRelatorio(yearf);
		ofstream file(caminho_ficheiro.c_str(), ios::out | ios::app);

		if(!file) return;

		if(yearf == (int) year)
			breakMonth = month - 1;
		else
			breakMonth = 12;

		while(monthf <= breakMonth) {

			if(monthf <= 0) break;

			writeMonth(file, monthf);

			for(vector<Condo *>::const_iterator it = condos.begin();
					it != condos.end(); ++it) {

				file << "[CONDOMINIO " << (*it)->getID() << "]: " << endl << endl;

				(*it)->writeCondoProfit(file, yearf, monthf);
				(*it)->writeCondoExpenses(file, yearf, monthf);
				(*it)->writeCommonSpacesExpenses(file, yearf, monthf);
				(*it)->writeExtInspectionsCalls(file, yearf, monthf);

				file << endl;

				writeEvents(file, yearf, monthf, (*it)->getID());

				file << endl;

				(*it)->writeServices(file, yearf, monthf);

				file << endl;

			}

			writeTechniciansWages(file, yearf, monthf);
			writeTotalInspections(file, yearf, monthf);

			monthf++;

		}

		yearf++;
		monthf = 1;
		file.close();

	}

}

void Company::writeTechniciansWages(ofstream & file, const int & year, const int & month) {
	pair<int, int> date = make_pair(year, month);

	if( total_wages.find(date) == total_wages.end() ) return;

	file << "[TECNICOS]: " << total_wages[date] << endl << endl;

	total_wages.erase(date);

}

void Company::writeTotalInspections(ofstream & file, const int & year, const int & month) {
	pair<int, int> date = make_pair(year, month);

	if( total_inspections.find(date) == total_inspections.end() ) return;
	if( total_inspections[date].size() == 0 ) return;

	file << "[INSPECTIONS]: " << endl;

	for(vector<pair<string, int> >::const_iterator it = total_inspections[date].begin();
			it != total_inspections[date].end(); ++it) {

		file << " " << (*it).first << ": " << (*it).second << endl;

	}

	total_inspections.erase(date);

	file << endl;
}

void Company::writeEvents(ofstream & file, const int & year, const int & month, const int & condo_id) {

	pair<int, int> date = make_pair(year, month);

	if( events.find(date) == events.end() ) return;

	if( events[date].first == condo_id ) {
		if( events[date].second ) {

			file << "Foi realizado o evento marcado pelo condominio " << condo_id << endl;

		} else {

			file << "O evento marcado pelo condominio " << condo_id << " foi cancelado por falta de confirmacao." << endl;

		}
	}

	events.erase(date);

}
/*
 * ==================================
 *          BST MANAGEMENT
 * ==================================
 */
BST<ExtInspection> Company::getExtInspectionsBST() const {
	return extInspectionsBST;
}

void Company::addExtInspectionToBST(ExtInspection & e) {
	extInspectionsBST.insert(e);
}

void Company::removeExtInspectionFromBST(ExtInspection & e) {
	extInspectionsBST.remove(e);
}

void Company::printExtInspections() const {
	extInspectionsBST.printTree();
}

bool Company::isExtInspectionsEmpty() const {
	return extInspectionsBST.isEmpty();
}

BSTItrIn<ExtInspection> Company::getBSTIteratorIn() const {

	BSTItrIn<ExtInspection> itr(extInspectionsBST);

	return itr;
}

size_t Company::callExtInspection(ExtInspection * e) {

	size_t cost = e->randomizeNewPrice(MAX_VARIATION);
	balance -= cost;

	return cost;
}

/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *             HASH TABLE
 * ==================================
 */
HashCondos Company::getOldCondosHashTable() const {
	return this->oldCondos;
}

void Company::addCondoToOldCondos(Condo & co) {
	oldCondos.insert(&co);
}

void Company::removeCondoFromOldCondos(Condo & co) {

	HashCondos::iterator it = oldCondos.find(&co);

	insertFreeID(co.getID());

	oldCondos.erase(it);

//	if(condos.size() == 0) return;
//	else {
//		condos[0]->decrementLastID();
//	}

}

Condo * Company::getOldCondoFromHashTable(Condo & co) const {

	HashCondos::const_iterator it = oldCondos.find(&co);

	if(it != oldCondos.end()) return *it;
	else throw HashCondos_Error();

}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *            PRIORITY QUEUE
 * ==================================
 */
HEAP_SALOON Company::getSaloonReservations() const {
	return saloon;
}

void Company::addReservation(Reservation & r) {
	saloon.push(r);
}

void Company::removeReservation(Reservation & r) {

	vector<Reservation> final;
	while(!saloon.empty()) {
		if( !(saloon.top() == r) ) final.push_back(saloon.top());
		saloon.pop();
	}

	for(vector<Reservation>::iterator it = final.begin();
			it != final.end(); ++it) saloon.push(*it);

}

pair<Reservation, bool> Company::validateReservations() {

	HEAP_SALOON tmp = saloon;
	vector<Reservation> new_queue;

	pair<Reservation, bool> state = make_pair(Reservation(), true);

	bool already_realized = false;
	while(!saloon.empty()) {

		if( year == saloon.top().getYear() ) {

			if( !saloon.top().getState() ) {

				if( saloon.top().getMonth() < month ) {

					insertEvent(saloon.top().getYear(), saloon.top().getMonth(),
							saloon.top().getCondo()->getID(), false);

					saloon.pop();
					continue;

				}


				if( (saloon.top().getMonth() - confirmationLimit ) < month ) {

					insertEvent(saloon.top().getYear(), saloon.top().getMonth(),
												saloon.top().getCondo()->getID(), false);

					saloon.pop();
					continue;

				}

				else if( (saloon.top().getMonth() - confirmationLimit ) == month ) {

					state.first = saloon.top();
					state.second = false;

				}

			} else {

				if( saloon.top().getMonth() <= month ) {

					insertEvent(saloon.top().getYear(), saloon.top().getMonth(),
							saloon.top().getCondo()->getID(), !already_realized);

					already_realized = true;

					saloon.pop();
					continue;

				}

			}

		}

		new_queue.push_back(saloon.top());
		saloon.pop();

	}

	for(vector<Reservation>::const_iterator it = new_queue.begin();
			it != new_queue.end(); ++it)
		saloon.push(*it);

	return state;

}

void Company::removeAllReservationsFromCondo(const int & condo_id) {

	HEAP_SALOON tmp = saloon;
	vector<Reservation> new_queue;

	while(!saloon.empty()) {

		if( saloon.top().getCondo()->getID() != condo_id ) {

			new_queue.push_back( saloon.top() );

		}

		saloon.pop();

	}

	for( vector<Reservation>::const_iterator it = new_queue.begin();
			it != new_queue.end(); ++it ) {

		saloon.push(*it);

	}


}

bool Company::validDate(const int & year, const int & month) const {

	if( (month < 1) || (month > 12) ) return false;

	if( year < (int) this->year ) return false;

	if( year == (int) this->year ) {

		if( month <= (int) this->month ) return false;
		if( month <= (int) (this->month - this->confirmationLimit) ) return false;

	}

	return true;
}
/*
 * ==================================
 * ==================================
 */
/*
 * ==================================
 *             OPERATORS
 * ==================================
 */
Company & Company::operator =(const Company & e) {
	this->name = e.getName();
	this->balance = e.getBalance();
	this->month = e.getMonth();
	this->year = e.getYear();
	this->startingDate = e.getInitialDate();
	this->owners = e.getOwners();
	this->technicians = e.getTechinicians();
	this->condos = e.getCondos();
	this->oldCondos = e.getOldCondosHashTable();
	this->inspections = e.getInspections();
	this->periodicity_default = e.getPeriodicityDefault();
	this->extInspectionsBST = e.getExtInspectionsBST();
	this->saloon = e.getSaloonReservations();
	this->confirmationLimit = e.getConfirmationLimit();
	this->free_condo_ids = e.getFreeIDs();

	return *this;
}

ostream & operator<<(ostream & o, const Company & e) {

	// Escreve cabeçalho
	o << COMPANY_HEADER << endl;
	o << e.getName() << DELIMITER << e.getBalance() << DELIMITER << e.getMonth() << DELIMITER << e.getYear()
			<< DELIMITER << e.getConfirmationLimit() << endl;

	map<string, pair<size_t, size_t> > grava = e.getInspections();
	for(map<string, pair<size_t, size_t> >::const_iterator it = grava.begin();
			it != grava.end(); ++it) {

		o << it->first << DELIMITER << it->second.first << DELIMITER << it->second.second << endl;

	}

	o << "default" << endl;
	map<string, size_t> default_grava = e.getPeriodicityDefault();
	for(map<string, size_t>::const_iterator it = default_grava.begin();
			it != default_grava.end(); ++it) {
		o << it->first << DELIMITER << it->second << endl;
	}

	return o;
}
/*
 * ==================================
 * ==================================
 */


