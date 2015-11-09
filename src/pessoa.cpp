#include "pessoa.h"
#include "propriedade.h"


/*
 * ==================================
 *          CONSTRUCTORS
 * ==================================
 */
Person::Person(const string & nome) : nome(nome) { }

Technician::Technician() : Person("default"), profissao("default"), salario(0), disponibilidade(true) { }
Technician::Technician(const string & nome, const string & profissao, const size_t & salario) :
		Person(nome), profissao(profissao), salario(salario), disponibilidade(true) { }

Owner::Owner() : Person("vazio") { }
Owner::Owner(const string & nome) : Person(nome) { }

/*
 * ==================================
 *           DESTRUCTORS
 * ==================================
 */
Person::~Person() { }
Technician::~Technician() { }
Owner::~Owner() { }

/*
 * ==================================
 *           MEMBER GETTERS
 * ==================================
 */
string Person::getNome() const {
	return this->nome;
}

string Technician::getProfissao() const {
	return this->profissao;
}

size_t Technician::getSalario() const {
	return this->salario;
}

vector<Property *> Owner::getPropriedades() const {
	return this->propriedades;
}

bool Technician::getDisponibilidade() const {
	return this->disponibilidade;
}

/*
 * ==================================
 *           MEMBER SETTERS
 * ==================================
 */
void Person::setNome(const string & nome) {
	this->nome = nome;
}

void Technician::setProfissao(const string & profissao) {
	this->profissao = profissao;
}

void Technician::setSalario(const size_t & salario) {
	this->salario = salario;
}

void Owner::adicionaPropriedade(Property * p) {
	this->propriedades.push_back(p);
}

void Owner::eliminaPropriedade(const size_t & index) {

	for(size_t i = 0; i < this->propriedades.size(); i++) {

		if (this->propriedades[i]->getID() == index) {

			this->propriedades.erase(this->propriedades.begin() + i);
			break;

		}
	}

}

void Owner::eliminaTodasPropriedades() {

	this->propriedades.clear();

}

void Technician::setDisponibilidade() {
	if(this->disponibilidade) this->disponibilidade = false;
	else this->disponibilidade = true;
}

void Owner::eliminaPropriedadesDeCondominio(const int & condo_id) {

	for(size_t i = 0; i < this->propriedades.size(); i++) {

		if(this->propriedades[i]->getID() == condo_id) {

			this->propriedades.erase(this->propriedades.begin() + i);

		}

	}

}

/*
 * ==================================
 *              OUTPUTS
 * ==================================
 */
ostream & Person::out(ostream & o) const {

	o << this->nome << endl;

	return o;

}

ostream & Technician::out(ostream & o) const {

	o << this->nome << DELIMITER << this->profissao << DELIMITER << this->salario << DELIMITER << this->disponibilidade <<endl;

	return o;

}

ostream & Owner::out(ostream & o) const {

	o << this->nome;

	return o;

}

/*
 * ==================================
 *             OPERATORS
 * ==================================
 */
ostream & operator<< (ostream & o, Person & p) {

	p.out(o);

	return o;

}

