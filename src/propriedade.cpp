#include "propriedade.h"

/*
 * CLASS CONSTRUCTORS
 */
Property::Property(const size_t & id_condominio, const size_t & area, const size_t & andar) :
	id(++lastID), id_condo(id_condominio), area(area), floor(andar),
	remaining_months(0), contractType(-1), hasOwner(false), owner(new Owner()) {}

Residence::Residence(const size_t & id_condominio, const size_t & area, const size_t & andar) : Property(id_condominio, area, andar) {}

Office::Office(const size_t & id_condominio, const size_t & area, const size_t & andar) : Property(id_condominio, area, andar) {}

Store::Store(const size_t & id_condominio, const size_t & area, const size_t & andar) : Property(id_condominio, area, andar) {}

/**
 * MEMBER GETTERS
 */
size_t Property::getID() const {
	return this->id;
}

size_t Property::getID_Condo() const {
	return this->id_condo;
}

size_t Property::getArea() const {
	return this->area;
}

size_t Property::getFloor() const {
	return this->floor;
}

size_t Property::getContractType() const {
	return this->contractType;
}

bool Property::existsOwner() const {
	return this->hasOwner;
}

double Residence::getValue() const {

	double valor_final = 0;

	/* Andar */
	// Assumi que quanto mais alto, melhor a vista, mais cara a renda.
	valor_final += (100 * this->floor);

	/* Área */
	// Obviamente que quanto maior a área mais cara a renda.
	// Preço : 0.25 por cada metro quadrado.
	valor_final += (0.75 * this->area);

	/* Tipo de Contrato */
	// Quanto maior o timespan menos se paga.

	if(this->contractType == 0) valor_final = (1.4*valor_final);
	else if(this->contractType == 1) valor_final = (1 * valor_final) * 6;
	// Quem paga de uma forma anual tem de ter desconto, é muito hardcore.
	else if(this->contractType == 2) valor_final = (0.8 * valor_final) * 12;

	return valor_final;
}

double Office::getValue() const {

	double valor_final = 0;

	/* Andar */
	// Assumi que quanto mais alto, melhor a vista, mais cara a renda (lol)
	// Mas com um peso inferior que na residência.
	valor_final += (80 * this->floor);

	/* Área */
	// Obviamente que quanto maior a área mais cara a renda.
	// Preço : 0.32 por cada metro quadrado.
	// Criei uma inflaccao por ser escritório. Não sei se isto existe, mas...
	valor_final += (1 * this->area);

	/* Tipo de Contrato */
	// Quanto maior o timespan menos se paga.

	if(this->contractType == 0) valor_final = (1.4*valor_final);
	else if(this->contractType == 1) valor_final = (1 * valor_final) * 6;
	// Quem paga de uma forma anual tem de ter desconto, é muito hardcore.
	else if(this->contractType == 2) valor_final = (0.8 * valor_final) * 12;

	return valor_final;

}

double Store::getValue() const {

	double valor_final = 0;

	/* Andar */
	// Neste caso assumi que quanto mais alto menor a renda...
	// Ninguém quer ter uma loja no décimo quinto andar.

	// Valor base para o caso ideal (andar = 0)
	valor_final += 300; // é uma loja...
	valor_final -= (3 * this->floor);

	/* Área */
	// Obviamente que quanto maior a área mais cara a renda.
	// Preço : 0.70 por cada metro quadrado.
	// Loja mais cara por metro quadrado, makes sense...
	valor_final += (1.25 * this->area);

	/* Tipo de Contrato */
	// Quanto maior o timespan menos se paga.

	if(this->contractType == 0) valor_final = (1.4*valor_final);
	else if(this->contractType == 1) valor_final = (1 * valor_final) * 6;
	// Quem paga de uma forma anual tem de ter desconto, é muito hardcore.
	else if(this->contractType == 2) valor_final = (0.8 * valor_final) * 12;

	return valor_final;

}

Owner * Property::getOwner() const {
	return this->owner;
}

void Property::setContract(const size_t & tipo) {
	this->contractType = tipo;
}

void Property::decrementMoths() {

	if(this->remaining_months == 0) {

		if(this->contractType == 0) this->remaining_months = 0;
		else if(this->contractType == 1) this->remaining_months = 5;
		else if(this->contractType == 2) this->remaining_months = 11;

	} else {

		this->remaining_months--;

	}
}

void Property::createContract(const size_t &tipoContrato, Owner * p) {

	this->contractType = tipoContrato;

	if(this->contractType == 0) this->remaining_months = 0;
	else if(this->contractType == 1) this->remaining_months = 5;
	else if(this->contractType == 2) this->remaining_months = 11;

	this->owner = p;
	this->hasOwner = true;
	this->owner->adicionaPropriedade(this);
}

void Property::setHasOwner(const bool & temProprietario) {
	this->hasOwner = temProprietario;
}

void Property::setRemainingMonths(const size_t & meses) {
	this->remaining_months = meses;
}

int Property::lastID = -1;

ostream & operator<< (ostream & o, Property * p) {

	p->out(o);

	return o;
}

ostream & Property::out(ostream & o) const {

	o << this->id_condo << DELIMITER << "propriedade" << DELIMITER << this->area << DELIMITER << this->floor << DELIMITER;

	if(hasOwner) o << this->owner->getNome() << DELIMITER;
	else o << -1 << DELIMITER;

	if(this->contractType == 0) o << "mensal";
	else if(this->contractType == 1) o << "semestral";
	else if(this->contractType == 2) o << "anual";
	else o << "nenhum";

	o << DELIMITER << this->remaining_months;

	o << endl;

	return o;

}

ostream & Residence::out(ostream & o) const {

	o << this->id_condo << DELIMITER << "residencia" << DELIMITER << this->area << DELIMITER << this->floor << DELIMITER;

	if(this->hasOwner) o << this->owner->getNome() << DELIMITER;
	else o << "-1" << DELIMITER;

	if(this->contractType == 0) o << "mensal";
	else if(this->contractType == 1) o << "semestral";
	else if(this->contractType == 2) o << "anual";
	else o << "nenhum";

	o << DELIMITER << this->remaining_months;

	o << endl;

	return o;

}

ostream & Store::out(ostream & o) const {

	o << this->id_condo << DELIMITER << "loja" << DELIMITER << this->area << DELIMITER << this->floor << DELIMITER;

	if(hasOwner) o << this->owner->getNome() << DELIMITER;
	else o << -1 << DELIMITER;

	if(this->contractType == 0) o << "mensal";
	else if(this->contractType == 1) o << "semestral";
	else if(this->contractType == 2) o << "anual";
	else o << "nenhum";

	o << DELIMITER << this->remaining_months;

	o << endl;

	return o;

}

ostream & Office::out(ostream & o) const {

	o << this->id_condo << DELIMITER << "escritorio" << DELIMITER << this->area << DELIMITER << this->floor << DELIMITER;

	if(hasOwner) o << this->owner->getNome() << DELIMITER;
	else o << -1 << DELIMITER;

	if(this->contractType == 0) o << "mensal";
	else if(this->contractType == 1) o << "semestral";
	else o << "anual";

	o << DELIMITER << this->remaining_months;

	o << endl;

	return o;

}

void Property::decrementID() {
	this->id--;
}

void Property::removeContract() {
	this->remaining_months = 0;
	this->hasOwner = false;
	this->contractType = -1;
}

size_t Property::getType() const {
	return 3; // Propriedade sem tipo definido.
}

size_t Residence::getType() const {
	return 0;
}

size_t Store::getType() const {
	return 1;
}

size_t Office::getType() const {
	return 2;
}

size_t Property::getRemainingMonths() const {
	return this->remaining_months;
}

void Property::resetMonths() {

	if(this->contractType == 0) this->remaining_months = 1;
	else if(this->contractType == 1) this->remaining_months = 6;
	else if(this->contractType == 2) this->remaining_months = 12;
	else return;
}


