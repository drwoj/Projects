#pragma once
#include <string>
#include <iostream>
using namespace std;

class Leader
{
	string m_nick;
	int m_score;

public:
	void setNick(string s);

	void setScore(int a);

	string getNick();

	int getScore();

	friend ostream& operator<< (ostream& out, Leader& leader);

	friend bool operator> (const Leader& l1, const Leader& l2);
};

