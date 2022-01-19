#include "Flight.h"


	Flight::Flight() :m_from("Undefined"), m_to("Undefined"), m_departure("Undefined"), 
		m_arrival("Undefined"), m_airlines("Undefined"), m_price(-1), m_available(-1) {};


	Flight::Flight(string from, string to, string departure, string arrival, string airlines, int price, bool available) :m_from(from), m_to(to), m_departure(departure), m_arrival(arrival),
		m_airlines(airlines),  m_price(price), m_available(available) {};


	

	string Flight::GetFrom() {
		return m_from;
	}

	string Flight::GetTo() {
		return m_to;
	}

	string Flight::GetDeparture() {
		return m_departure;
	}

	string Flight::GetArrival() {
		return m_arrival;
	}

	string Flight::GetAirlines() {
		return m_airlines;
	}

	int Flight::GetPrice() {
		return m_price;
	}

	bool Flight::GetAvailable() {
		return m_available;
	}


ostream& operator<< (ostream& out, Flight& x) {

	out << x.m_from << " " << x.m_to << " " << x.m_departure << " " << x.m_arrival << " " << x.m_airlines << " "<< x.m_price <<" "<<x.m_available;

	return out;
}
istream& operator>> (istream& in, Flight& x) {

	in >> x.m_from >> x.m_to >> x.m_departure >> x.m_arrival >> x.m_airlines >> x.m_price >> x.m_available;

	return in;
}

bool operator== (const Flight& x1, const Flight& x2) {

	if (x1.m_airlines != x2.m_airlines)
		return false;

	if (x1.m_from != x2.m_from)
		return false;

	if (x1.m_to != x2.m_to)
		return false;

	if (x1.m_arrival != x2.m_arrival)
		return false;

	if (x1.m_departure != x2.m_departure)
		return false;

	if (x1.m_price != x2.m_price)
		return false;

	if (x1.m_available != x2.m_available)
		return false;
	
	return true;
}