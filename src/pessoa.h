#ifndef PESSOA_H_
#define PESSOA_H_

#include <string>
#include <vector>
#include <iostream>

#include "strings.h"

class Property;

using namespace std;

/**
 * Class Pessoa. Main class containing the classes Tecnico and Proprietario.
 */
class Person {
protected:
	string nome; 			/**< Name of the Pessoa. */

public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Contructor of Pessoa.
	 * @param nome Pessoa's name.
	 */
	Person(const string & nome);
	/*
	 * ==================================
	 * ==================================
	 */
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destructor of Pessoa.
	 */
	virtual ~Person();
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
	 * Gets the name of the Pessoa.
	 * @return Pessoa's name.
	 */
	string getNome() const;
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
	 * Sets the name of the Pessoa.
	 * @param nome Name of the Pessoa.
	 */
	void setNome(const string & nome);
	/*
	 * ==================================
	 * ==================================
	 */
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Overload of the << operador.
	 * @param o ostream.
	 * @param p Pessoa who's parameters are to be passed to the ostream.
	 * @return ostream with the Pessoas's parameters.
	 */
	friend ostream & operator<< (ostream & o, Person & p);
	/**
	 * Function of Pessoa.
	 * @param o ostream.
	 * @return ostream with the Pessoas's parameters.
	 */
	virtual ostream & out(ostream & o) const;
};

/**
 * Class Tecnico. Subclass of Pessoa.
 */
class Technician : public Person {
protected:
	string profissao; 		/**< Tecnicos profession. */
	size_t salario; 		/**< Tecnicos salary. */
	bool disponibilidade;	/**< Tecnicos availability. */

public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Default constructor of Tecnico.
	 */
	Technician();
	/**
	 * Construtor de Tecnico.
	 * @param nome Tecnico's name.
	 * @param profissao Tecnico's profession.
	 * @param salario Tecnico's salary.
	 */
	Technician(const string & nome, const string & profissao, const size_t & salario);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destructor of Tecnico.
	 */
	~Technician();
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Gets the profession of the Tecnico.
	 * @return Tecnico's profession.
	 */
	string getProfissao() const;
	/**
	 * Gets the salary of the Tecnico.
	 * @return Tecnico's salary.
	 */
	size_t getSalario() const;
	/**
	 * Gets the availability of the Tecnico.
	 * @return true If available, false otherwise.
	 */
	bool getDisponibilidade() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Sets the salary of the Tecnico.
	 * @param salario Tecnico's salary.
	 */
	void setSalario(const size_t & salario);
	/**
	 * Sets the profession of the Tecnico.
	 * @param profissao Tecnico's profession.
	 */
	void setProfissao(const string & profissao);
	/**
	 * Changes the availability of the Tecnic:
	 * 	True->False,
	 * 	False->True.
	 */
	void setDisponibilidade();
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Function of Tecnico.
	 * @param o ostream.
	 * @return ostream with the Tecnico's parameters.
	 */
	ostream & out (ostream & o) const;
};

/**
 * Class Proprietario. Subclass of Pessoa.
 */
class Owner : public Person {
protected:
	vector<Property *> propriedades;		/**< Vector of pointers to the Propriedades of the Proprietario. */

public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Default constructor of Proprietario.
	 */
	Owner();
	/**
	 * Constructor of Proprietario.
	 * @param nome Proprietario's name.
	 */
	Owner(const string & nome);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destructor of Proprietario.
	 */
	~Owner();
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	 /**
	  * Gets the Propriedades of the Proprietario.
	 * @return Vector of pointers to the Propriedades of the Proprietario.
	 */
	vector<Property *> getPropriedades() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Adds a Propriedade to propriedades.
	 * @param p Propriedade to add.
	 */
	void adicionaPropriedade(Property * p);
	/**
	 * Removes a Propriedade from propriedades.
	 * @param index Propriedade's index
	 */
	void eliminaPropriedade(const size_t & index);
	/**
	 * Removes all Propriedades from propriedades.
	 */
	void eliminaTodasPropriedades();
	/**
	 * Removes all Propriedades from propriedades belonging to a certain Condominio.
	 * @param id_condominio ID of the Condominio.
	 */
	void eliminaPropriedadesDeCondominio(const int & condo_id);
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Function of Tecnico.
	 * @param o ostream.
	 * @return ostream with the Proprietario's parameters.
	 */
	ostream & out (ostream & o) const;
};


#endif /* PERSON_H_ */
