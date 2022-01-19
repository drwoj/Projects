#include "Diver.h"

	Diver::Diver(string name, string surname, string certificate, int age, int dives, int ID) : m_name(name), m_surname(surname), m_certificate(certificate), m_age(age), m_dives(dives), m_ID(ID) {};

	Diver::Diver():m_name(""), m_surname(""), m_certificate(""), m_age(-1), m_dives(-1), m_ID(-1) {};

	string Diver::GetName() { return m_name; };

	string Diver::GetSurname() { return m_surname; };

	string Diver::GetCertificate() { return m_certificate; };

	int Diver::GetAge() { return m_age; };

	int Diver::GetDives() { return m_dives; };

	int Diver::GetID() { return m_ID; };

	ostream& operator<<(ostream& out, Diver& x) {

		out << x.m_name << " " << x.m_surname << " " << x.m_certificate << " " << x.m_age << " " << x.m_dives << " " << x.m_ID;
		return out;
	}

	istream& operator>>(istream& in, Diver& x) {

		in >> x.m_name >> x.m_surname >> x.m_certificate >> x.m_age >> x.m_dives >> x.m_ID;

		return in;
	}

	bool operator== (const Diver& x1, const Diver& x2) {

		if (x1.m_ID != x2.m_ID)
			return false;

		return true;
	}
