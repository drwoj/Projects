#pragma once

#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Diver {

private:
	string m_name;
	string m_surname;
	string m_certificate;
	int m_age;
	int m_dives;
	int m_ID;

public:

	Diver();

	Diver(string name, string surname, string certificate, int age, int dives, int ID);

	string GetName();

	string GetSurname();

	string GetCertificate();

	int GetAge();

	int GetDives();

	int GetID();

	friend ostream& operator<< (ostream& out, Diver& x);
	friend istream& operator>> (istream& in, Diver& x);
	friend bool operator== (const Diver& x1,const Diver& x2);
};

ostream& operator<< (ostream& out,Diver& x);
istream& operator>> (istream& in, Diver& x);
bool operator== (const Diver& x1, const Diver& x2);