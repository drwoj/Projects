#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Flight
{
private:

	string m_from;
	string m_to;
	string m_departure;
	string m_arrival;
	string m_airlines;
	int m_price;
	bool m_available;

public:
	
	Flight();

	Flight(string from, string to, string departure, string arrival, string airlines, 
		int price, bool available);

	string GetFrom();

	string GetTo();

	string GetDeparture();

	string GetArrival();

	string GetAirlines();

	int GetPrice();

	bool GetAvailable();

	friend ostream& operator<< (ostream& out, Flight& x);
	friend istream& operator>> (istream& in, Flight& x);
	friend bool operator== (const Flight& x1, const Flight& x2);
};

ostream& operator<< (ostream& out, Flight& x);
istream& operator>> (istream& in, Flight& x);
bool operator== (const Flight& x1, const Flight& x2);