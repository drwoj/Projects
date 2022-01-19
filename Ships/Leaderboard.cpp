#include "Leaderboard.h"

void Leaderboard::check(Player& p)
{
	int k = 0;
	for (int i = 0; i < m_leaders.size(); i++)
	{
		if ((*m_leaders[i]).getScore() > p.getScore())
			k++;
	}

	if (k < 10)
	{
		Leader l;
		l.setNick(p.getNick());
		l.setScore(p.getScore());

		m_leaders.emplace(m_leaders.begin()+k, make_shared<Leader>(l));
		sort();
		load();
	}
	
}

void Leaderboard::getLeaders()
{
	ifstream file;
	file.open("Leaderboard.txt");
	if (file.good())
	{
		string nick;
		int score;
		for (int i = 0; i < 10; i++)
		{
			file >> nick >> score;
			Leader l;
			l.setNick(nick);
			l.setScore(score);

			m_leaders.push_back(make_shared<Leader>(l));

			if (file.eof())
				break;
		}
		file.close();
	}

	file.close();
}

void Leaderboard::show()
{
	cout << endl<<"tabela liderow" << endl;
	for (int i = 0; i <10; i++)
	{
		cout << i + 1 <<". "<< (*m_leaders[i]);
	}
}

void Leaderboard::load()
{
	ofstream file;
	file.open("Leaderboard.txt");

	if (file.good())
	{
		for (int i = 0; i <10; i++)
			file << (*m_leaders[i]);

	}
}

void Leaderboard::swap(Leader &l1, Leader &l2)
{
	Leader buf = l1;
	l1 = l2;
	l2 = buf;
}

void Leaderboard::sort() //sorowanie b¹belkowe
{
	for (int i=0; i<m_leaders.size(); i++)
		for (int j = 0; j < m_leaders.size(); j++)
			if ((*m_leaders[i]) > (*m_leaders[j]))
				swap((*m_leaders[i]), (*m_leaders[j]));

}