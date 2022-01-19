#include "User.h"

	void User::addBullet(int x, int y, int hit)
	{
		Bullet b(x, y, hit);
		m_bullets.push_back(make_shared<Bullet>(b));
	}

	vector<shared_ptr<Bullet>> User::getBullets()
	{
		return m_bullets;
	}

	void User::addShip(int x, int y, int size, bool horizontal)
	{
		Ship s(x, y, size, horizontal);
		m_ships.push_back(make_shared<Ship>(s));
	}

	vector<shared_ptr<Ship>>User::getShips()
	{
		return m_ships;
	}

	void User::alive(int i)
	{
		m_ships.erase(m_ships.begin() + i);
		cout << endl << "Statek zatopiony!" << endl;	
	}

	bool User::collision(int x, int y, int size, bool orientation) // 0 - poziomo 
	{
		for (int i = 0; i < m_ships.size(); i++)
			for (int j = 0; j < (*m_ships[i]).getParts().size(); j++)
				for (int k = -1; k < size + 1; k++)
				{
					if (!orientation)
						if (x + k == (*(*m_ships[i]).getParts()[j]).getX() && (y == (*(*m_ships[i]).getParts()[j]).getY() || y + 1 == (*(*m_ships[i]).getParts()[j]).getY() || y - 1 == (*(*m_ships[i]).getParts()[j]).getY()))
							return true;

					if (orientation)

						if ((x - 1 == (*(*m_ships[i]).getParts()[j]).getX() || x + 1 == (*(*m_ships[i]).getParts()[j]).getX() || x == (*(*m_ships[i]).getParts()[j]).getX()) && y + k == (*(*m_ships[i]).getParts()[j]).getY())
							return true;
				}
		return false;
	}

	void User::shots()
	{
		fstream file;
		file.open("log.txt", ios::out | ios::app);
		if (file.good())
		{
			for (int i = 0; i < m_shots.size(); i++)
			{
				file << setw(3)<< i << m_shots[i];
			}
		}
		file.close();
	}

	void User::addShot(int x, int y, int hit)
		{
			Bullet b(x, y ,hit);
			m_shots.push_back(b);
		}

	vector<Bullet> User::getShots()
	{
		return m_shots;
	}
