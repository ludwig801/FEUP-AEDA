/*
 * propriedade.h
 *
 *  Created on: Oct 16, 2013
 *      Author: kevin
 */

#ifndef PROPRIEDADE_H_
#define PROPRIEDADE_H_

#include <string>
#include <iostream>
#include <vector>

#include "pessoa.h"
#include "strings.h"

using namespace std;


/**
 *
 * Class Propriedade. Contains all types of units (Residencia, Escritorio, Loja).
 *
 */
class Property {
protected:
	size_t id;								/**< ID of the Propriedade.*/
	size_t id_condo;						/**< ID of the Propriedade's Condominio. */
	size_t area;							/**< Propriedade's area.*/
	size_t floor;							/**< Propriedade's floor.*/
	size_t remaining_months;				/**< Months remaining to payment of the next parcel. */
	int contractType;						/**< Type of contract. */
	bool hasOwner;							/**< Specifies if the propriedade has or not a Proprietario. */
	Owner * owner;							/**< Pointer to the Proprietario. */

	static int lastID;						/**< ID of the last Propriedade. */
public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Constructor of Propriedade.
	 * @param id_condominio Condominio's ID.
	 * @param area Propriedade's area.
	 * @param andar Propriedade's floor.
	 */
	Property(const size_t & id_condo, const size_t & area, const size_t & floor);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destructor of Propriedade.
	 */
	virtual ~Property() { }
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Gets the ID of the Propriedade.
	 * @return Propriedade's ID.
	 */
	size_t getID() const;
	/**
	 * Gets the ID of the Propriedade's Condominio.
	 * @return Condominio's ID.
	 */
	size_t getID_Condo() const;
	/**
	 * Gets the area of the Propriedade.
	 * @return Propriedade's area.
	 */
	size_t getArea() const;
	/**
	 * Gets the floor of the Propriedade.
	 * @return Propriedade's floor.
	 */
	size_t getFloor() const;
	/**
	 * Gets the type of contract of the Propriedade.
	 * @return Propriedades' contract type.
	 */
	size_t getContractType() const;
	/**
	 * Gets the parcel of the Propriedade (only aplicable to the Subclasses).
	 * @return Propriedade's parcel.
	 */
	virtual double getValue() const = 0;
	/**
	 * Gets the current status of the Propriedade (vacant or not).
	 * @return true If there is a Proprietario, false otherwise.
	 */
	bool existsOwner() const;
	/**
	 * Gets the Proprietario of the Propriedade.
	 * @return Pointer to the Proprietario.
	 */
	Owner * getOwner() const;
	/**
	 * Returns the type of Propriedade:
	 * 	0: residencia
	 * 	1: loja
	 * 	2: escritorio
	 * 	3: <undefined>
	 *
	 * @return Propriedade's type.
	 */
	virtual size_t getType() const;
	/**
	 * Gets the remaining months before next parcel's payment.
	 * @return Remaining months.
	 */
	size_t getRemainingMonths() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Sets the type of contract.
	 * @param tipo Contract's type.
	 */
	void setContract(const size_t & tipo);
	/**
	 * Changes the current status of the property (vacant or not).
	 * @param temProprietario Status to set.
	 */
	void setHasOwner(const bool & temProprietario);
	/**
	 * Decrements the Propriedade's ID.
	 */
	void decrementID();
	/**
	 * Decrements the remaining months before next parcel's payment.
	 */
	void decrementMoths();
	/**
	 * Resets the remaining months before next parcel's payment.
	 * This function is called upon each payment.
	 */
	void resetMonths();
	/**
	 * Associates a new contract.
	 * @param tipoContrato Contract's type.
	 * @param p Pointer to the new Proprietario of the Propriedade.
	 */
	void createContract(const size_t & tipoContrato, Owner * p);
	/**
	 * Removes the associated contract.
	 */
	void removeContract();
	/**
	 * Sets the remaining months before next parcel's payment.
	 * @param meses Months to set.
	 */
	void setRemainingMonths(const size_t & meses);
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Overload of the << operador.
	 * @param o ostream.
	 * @param p Propriedade to print.
	 * @return ostream with the Propriedade's parameters.
	 */
	friend ostream & operator<< (ostream & o, Property * p);
	/**
	 * Function of Propriedade.
	 * @param o ostream.
	 * @return ostream with the Propriedade's parameters.
	 */
	virtual ostream & out (ostream & o) const;
};

/**
 *
 * Classe Residencia. Referente a unidades de apartamentos.
 *
 */
class Residence: public Property {
public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Construtor de Residencia.
	 * @param id_condominio ID do condominio a receber a residencia.
	 * @param area size_t com area da unidade.
	 * @param andar size_t com o andar da unidade.
	 */
	Residence(const size_t & id_condominio, const size_t & area, const size_t & andar);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destrutor de Residencia.
	 */
	~Residence() { }
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Devolve o valor da unidade. Este valor varia consoante a area e o andar.
	 * @return double com o valor da Residencia.
	 */
	double getValue() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/**
	 * Retorna o tipo de propriedade.
	 * @return tipo Tipo de propriedade.
	 */
	size_t getType() const;
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Constroi uma ostream.
	 * @param o ostream que recebe a stream final.
	 * @return ostream final.
	 */
	ostream & out (ostream & o) const;
};

/**
 *
 * Classe Escritorio. Referente a unidades de escritorios.
 *
 */
class Office: public Property {
public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Construtor de Escritorio.
	 * @param id_condominio ID do condominio a receber a residencia.
	 * @param area size_t com area da unidade.
	 * @param andar size_t com o andar da unidade.
	 */
	Office(const size_t & id_condominio, const size_t & area, const size_t & andar);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destrutor de escritorio.
	 */
	~Office() { }
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Devolve o valor do Escritorio. Este valor varia consoante a area e o andar.
	 * @return double com valor do Escritorio.
	 */
	double getValue() const;
	/**
	 * Retorna o tipo de propriedade.
	 * @return tipo Tipo de propriedade.
	 */
	size_t getType() const;
	/*
	 * ==================================
	 *           MEMBER SETTERS
	 * ==================================
	 */
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Constroi uma ostream.
	 * @param o ostream que recebe a stream final.
	 * @return ostream final.
	 */
	ostream & out (ostream & o) const;
};

/**
 *
 * Classe Loja. Referente a unidades comerciais.
 *
 */
class Store: public Property {
public:
	/*
	 * ==================================
	 *          CONSTRUCTORS
	 * ==================================
	 */
	/**
	 * Construtor de Loja.
	 * @param id_condominio ID do condominio a receber a residencia.
	 * @param area size_t com area da unidade.
	 * @param andar size_t com o andar da unidade.
	 */
	Store(const size_t & id_condominio, const size_t & area, const size_t & andar);
	/*
	 * ==================================
	 *           DESTRUCTOR
	 * ==================================
	 */
	/**
	 * Destrutor de loja.
	 */
	~Store() { }
	/*
	 * ==================================
	 *           MEMBER GETTERS
	 * ==================================
	 */
	/**
	 * Devolve o valor da unidade. Este valor varia consoante a area e o andar.
	 * @return double com valor da Loja.
	 */
	double getValue() const;
	/**
	 * Retorna o tipo de propriedade.
	 * @return tipo Tipo de propriedade.
	 */
	size_t getType() const;
	/*
	 * ==================================
	 *             OPERATORS
	 * ==================================
	 */
	/**
	 * Constroi uma ostream.
	 * @param o ostream que recebe a stream final.
	 * @return ostream final.
	 */
	ostream & out (ostream & o) const;
};


#endif /* PROPRIEDADE_H_ */
