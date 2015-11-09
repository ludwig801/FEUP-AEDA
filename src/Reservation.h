/*
 * Reservation.h
 *
 *  Created on: 18/12/2013
 *      Author: Kevin
 */

#ifndef RESERVATION_H_
#define RESERVATION_H_

#include "condominio.h"

class Reservation {

	Condo * c;
	int month;
	int year;

	bool state;

public:

	Reservation() : c(new Condo()), month(1), year(1), state(false) { c->decrementLastID(); }
	Reservation(Condo * c, int & month, int & year, bool state = false) : c(c), month(month), year(year), state(state) { }
	~Reservation() { }

	Condo * getCondo() const { return c; }
	int getMonth() const { return month; }
	int getYear() const { return year; }
	bool getState() const { return state; }

	void setMonth(int & month) { this->month = month; }
	void setYear(int & year) { this->year = year; }
	void setState(bool & state) { this->state = state; }

	bool operator== (const Reservation & r) const {
		return ( (c == r.getCondo()) &&
				(month == r.getMonth()) &&
				(year == r.getYear()) );
	}

	bool operator< (const Reservation & r) const {

		if( year == r.getYear() ) {

			if( month == r.getMonth() ) {

				return (c->getTotalValue() < r.getCondo()->getTotalValue());

			}

			return month > r.getMonth();

		}

		return year > r.getYear();
	}

};





#endif /* RESERVATION_H_ */
