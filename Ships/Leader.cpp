#include "Leader.h"



	void Leader::setNick(string s)
	{
		m_nick = s;
	}

	void Leader::setScore(int a)
	{
		m_score = a;
	}

	string Leader::getNick()
	{
		return m_nick;
	}

	int Leader:: getScore()
	{
		return m_score;
	}

	ostream& operator<< (ostream& out, Leader& leader)
	{
		out << leader.m_nick<<" "<< leader.m_score << endl;
		return out;
	}

	bool operator> (const Leader& l1,const Leader& l2)
	{
		return l1.m_score > l2.m_score;
	}

