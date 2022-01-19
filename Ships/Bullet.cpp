#include "Bullet.h"

	int Bullet::getX()
	{
		return m_x;
	}

	int Bullet::getY()
	{
		return m_y;
	}

	void Bullet::allHit()
	{
		m_hit = 2;
	}

	int Bullet::getHit()
	{
		return m_hit;
	}

	Bullet::Bullet(int x, int y, int hit) : m_x{ x }, m_y{ y }, m_hit{ hit } {}
	

	ostream& operator<< (ostream& out, const Bullet& bullet)
	{
		out << ". Strzal w pole " << (char)(bullet.m_y+65) << bullet.m_x << " byl ";

		if (bullet.m_hit == 0)
		{
			out << "pudlem " << endl;
			return out;
		}

		if (bullet.m_hit == 1)
		{
			out << "trafieniem " << endl;
			return out;
		}

		if (bullet.m_hit == 2)
		{
			out << "strzalem zatapiajacym " << endl;
			return out;
		}

		return out;
	}
	

