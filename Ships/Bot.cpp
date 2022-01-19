#include "Bot.h"
#include "Player.h"

	void Bot::where(int size, Bot& b)
	{
		bool orientation = false;
		int y;
		int x;
		bool o;
		while (true)
		{

			y = (rand() % 10);
			x = (rand() % 10);


			if (size > 1)
			{

				if (x + size > 10 && y + size > 10)
				{
					continue;
				}

				while (true)
				{
					o = (rand() % 2);

					if (o)
					{
						if (x + size > 10)
						{
							continue;
						}
						orientation = false;
						break;
					}

					if (!o)
					{
						if (y + size > 10)
						{
							continue;
						}
						orientation = true;
						break;
					}

				}

			}
			if (collision(x, y, size, orientation))
			{
				continue;
			}
			break;
		}
		addShip(x, y, size, orientation);
	}

	void Bot::coords(Player& p)	// last: 4. lewo | 2. prawo | 3. dó³ | 1. góra
	{
		int x, y;
		

		if (!target)
		{
			while (true)
			{
				bool good = true;
				x = (rand() % 10);
				y = (rand() % 10);

				for (int i = 0; i < m_bullets.size(); i++)
					if ((*m_bullets[i]).getX() == x && (*m_bullets[i]).getY() == y)
						good = false;

				if (good) 
					break;		
			}

			m_x = x;
			m_y = y;
			return;
		}

	
		up = true;
		down = true;
		left = true;
		right = true;
		
		if (target && !wasHit && counter > 1)
		{
			if (horizontal)
			{
				m_x = m_x + counter + 1;
				return;
			}
			
			m_y = m_y + counter + 1;
			return;
			
		}


		if (target && !wasHit) // last: 4. lewo | 2. prawo | 3. dó³ | 1. góra
		{
			
			if (last == 4)
			{
				for (int i = 0; i < m_bullets.size(); i++)
				{

					if (m_x < 8 && m_x + 2 == (*m_bullets[i]).getX() && m_y == (*m_bullets[i]).getY()) // prawo
					{
						right = false;
					}

					if (m_x+1 == (*m_bullets[i]).getX() && m_y - 1 == (*m_bullets[i]).getY() && m_y > 0)	// dó³				
					{
						down = false;
					}

					if (m_x +1== (*m_bullets[i]).getX() && m_y + 1 == (*m_bullets[i]).getY() && m_y < 9)	// góra			
					{
						up = false;
					}
				}

				if (right)
				{
					m_x+=2;
					last = 2;
					return;
				}

				if (down)
				{
					m_x++;
					m_y--;
					last = 3;
					return;
				}

				if (up)
				{
					m_x++;
					m_y++;
					last = 1;
					return;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (last == 3)
			{
				for (int i = 0; i < m_bullets.size(); i++)
				{

					if (m_x < 9 && m_x  == (*m_bullets[i]).getX() && m_y+1 == (*m_bullets[i]).getY()) // prawo
					{
						right = false;
					}

					if (m_x-1 == (*m_bullets[i]).getX() && m_y + 1 == (*m_bullets[i]).getY() && m_y > 0)	// lewo		
					{
						left = false;
					}

					if (m_x == (*m_bullets[i]).getX() && m_y + 2 == (*m_bullets[i]).getY() && m_y < 8)	// góra			
					{
						up = false;
					}
				}

				if (right)
				{
					m_x++;
					m_y++;
					last = 2;
					return;
				}

				if (left)
				{
					m_x--;
					m_y++;
					last = 4;
					return;
				}

				if (up)
				{
					m_y+=2;
					last = 1;
					return;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (last == 1)
			{
				for (int i = 0; i < m_bullets.size(); i++)
				{

					if (m_x < 9 && m_x == (*m_bullets[i]).getX() && m_y - 1 == (*m_bullets[i]).getY()) // prawo
					{
						right = false;
					}

					if (m_x - 1 == (*m_bullets[i]).getX() && m_y - 1 == (*m_bullets[i]).getY() && m_x>0)	// lewo		
					{
						left = false;
					}

					if (m_x == (*m_bullets[i]).getX() && m_y - 2 == (*m_bullets[i]).getY() && m_y >1)	// dó³		
					{
						down = false;
					}
				}

				if (right)
				{
					m_x++;
					m_y--;
					last = 2;
					return;
				}

				if (left)
				{
					m_x--;
					m_y--;
					last = 4;
					return;
				}

				if (down)
				{
					m_y -= 2;
					last = 4;
					return;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			if (last == 2)
			{
				for (int i = 0; i < m_bullets.size(); i++)
				{

					if (m_x > 1 && m_x - 2 == (*m_bullets[i]).getX() && m_y == (*m_bullets[i]).getY()) // lewo
					{
						left = false;
					}

					if (m_x - 1 == (*m_bullets[i]).getX() && m_y - 1 == (*m_bullets[i]).getY() && m_y > 0)	// dó³				
					{
						down = false;
					}

					if (m_x - 1 == (*m_bullets[i]).getX() && m_y + 1 == (*m_bullets[i]).getY() && m_y < 9)	// góra			
					{
						up = false;
					}
				}

				if (left)
				{
					m_x -= 2;
					last = 2;
					return;
				}

				if (down)
				{
					m_x--;
					m_y--;
					last = 3;
					return;
				}

				if (up)
				{
					m_x--;
					m_y++;
					last = 1;
					return;
				}
			}
		}


		if (wasHit && target && counter ==2)
		{
			if (last == 2 || last == 4)
			{
				horizontal = true;
					if (last ==2 && m_x<9)
					{
						m_x++;
						return;
					}
					m_x--;
					return;
			}

			if (last == 1 || last == 3)
			{
				horizontal =false;
				if (last == 1 && m_y < 9)
				{
					m_y++;
					return;
				}
				m_y--;
				return;
			}

		}


		if (wasHit && target)
		{
			for (int i = 0; i < m_bullets.size(); i++)
			{

				if (m_x > 1 && m_x - 1 == (*m_bullets[i]).getX() && m_y == (*m_bullets[i]).getY()) // lewo
				{
					left = false;
				}

				if (m_x == (*m_bullets[i]).getX() && m_y - 1 == (*m_bullets[i]).getY() && m_y > 1)	// dó³				
				{
					down = false;
				}

				if (m_x < 8 && m_x + 1 == (*m_bullets[i]).getX() && m_y == (*m_bullets[i]).getY()) // prawo
				{
					right = false;
				}
				

				if (m_x == (*m_bullets[i]).getX() && m_y + 1 == (*m_bullets[i]).getY() && m_y < 8)	// góra			
				{
					up = false;
				}
			}

			if (left && m_x>0)
			{
				m_x--;
				last = 4;
				return;
			}

			if (right && m_x<9)
			{
				m_x++;
				last = 2;
				return;
			}

			if (down && m_y>0)
			{
				m_y--;
				last = 3;
				return;
			}

			if (up && m_y<9)
			{
				m_y++;
				last = 1;
				return;
			}

		}			

	}

	bool Bot::shot(Player& p)
			{
				for (int i = 0; i < p.getShips().size(); i++)
				{
					for (int j = 0; j < (*p.getShips()[i]).getParts().size(); j++)
					{
						if ((*(*p.getShips()[i]).getParts()[j]).getX() == m_x && (*(*p.getShips()[i]).getParts()[j]).getY() == m_y)
						{
							wasHit = true;
							counter++;
							target = true;
							(*(*p.getShips()[i]).getParts()[j]).damage();
							if ((*p.getShips()[i]).sink())
							{
								p.dmg();
								cout << "PRZECIWNIK ZATOPIL TWOJ STATEK!: " << (char)(m_y + 65) <<  m_x << endl;
								counter = 0;
								wasHit = false;
								target = false;
								int size = (*p.getShips()[i]).getSize();

								for (int k = 0; k < size; k++)
									for (int l = 0; l < m_bullets.size(); l++)
										if ((*m_bullets[l]).getX() == (*(*p.getShips()[i]).getParts()[k]).getX() && (*m_bullets[l]).getY() == (*(*p.getShips()[i]).getParts()[k]).getY())
										{
											(*m_bullets[l]).allHit();

											break;
										}
								addBullet(m_x, m_y, 2);
								addShot(m_x, m_y, 2);


								int y = (*p.getShips()[i]).getY();
								int x = (*p.getShips()[i]).getX();

								if ((*p.getShips()[i]).getOrientation())
								{

									for (int l = y - 1; l < (size + 1 + y); l++)
									{
										addBullet(x - 1, l, 0);
										addBullet(x + 1, l, 0);

									}
									addBullet(x, y - 1, 0);
									addBullet(x, y + size, 0);

								}
								else
								{

									for (int l = x - 1; l < (size + 1 + x); l++)
									{
										addBullet(l, y - 1, 0);
										addBullet(l, y + 1, 0);

									}
									addBullet(x - 1, y, 0);
									addBullet(x + size, y, 0);

								}


								p.alive(i);
							}
							else
							{
								cout << "PRZECIWNIK CIE TRAFIL!: " << (char)(m_y + 65) << m_x << endl;
								addBullet(m_x, m_y, 1);
								addShot(m_x, m_y, 1);
							}

							return true;
						}
					}
				}
				wasHit = false;
				cout << "PRZECIWNIK SPUDLOWAL!: " <<(char)(m_y+65)<<m_x << endl;
				addBullet(m_x, m_y, 0);
				addShot(m_x, m_y, 0);
				return false;
			}

	bool Bot::stop()
	{
		cout << "Zycie Przeciwnika: "<<m_hp<< endl;
		if (m_hp==0)
		{
			cout << endl << "KONIEC GRY!" << endl << "ODNIOSLES ZWYCIESTWO! " << endl;
			return true;
		}
		return false;

	}

	void Bot::dmg()
	{
		m_hp--;
	}

	int Bot::getHp()
	{
		return m_hp;
	}

	void Bot::display(Player& p, Bot& b)
	{
		cout << endl <<endl<<endl<< "Flota Przeciwnika: " << endl;
		int draw;
		cout << endl << " ";
		for (int i = 0; i < 10; i++)
			cout << setw(3) << i;
		cout << endl << endl;

		for (int i = 0; i < 10; i++)
		{
			cout << (char)(65 + i);
			////////////////////////////////////////////////////////////////////////////////
			for (int j = 0; j < 10; j++)
			{
				draw = 0;
				for (int k = 0; k < p.getBullets().size(); k++)
				{
					if ((*p.getBullets()[k]).getX() == j && (*p.getBullets()[k]).getY() == i)
					{
						draw = 1;

						if ((*p.getBullets()[k]).getHit() == 1)  // jesli trafienie
							draw = 2;
						if ((*p.getBullets()[k]).getHit() == 2)  // jesli zatopienie
							draw = 3;

						break;
					}

				}
				if (draw == 0)
					cout << setw(3) << ".";

				else if (draw == 1)
					cout << setw(3) << " ";

				else if (draw == 2)
					cout << setw(3) << "#";

				else if (draw == 3)
					cout << setw(3) << "X";


				//////////////////////////////////////////////////////////////////////////////////
			}
			cout << setw(3) << (char)(65 + i);
			cout << endl << endl;
		}
		cout << " ";
		for (int i = 0; i < 10; i++)
			cout << setw(3) << i;
		return;
	}
		
	void Bot::load1()
	{
		fstream file;
		file.open("log.txt", ios::out | ios::app);
		if (file.good())
		{
			file << "Poczatkowe ustawienie Komputera: "  << endl;

			file << endl << " ";
			for (int i = 0; i < 10; i++)
				file << setw(3) << i;
			file << endl<<endl;

			for (int i = 0; i < 10; i++)
			{
				file << (char)(65 + i);
				////////////////////////////////////////////////////////////////////////////////
				for (int j = 0; j < 10; j++)
				{
					int draw = 0;
					for (int s = 0; s < m_ships.size(); s++)
					{
						for (int p = 0; p < (*m_ships[s]).getParts().size(); p++)
						{
							if ((*(*m_ships[s]).getParts()[p]).getX() == j && (*(*m_ships[s]).getParts()[p]).getY() == i)
								draw = 1;

						}
					}

					if (draw == 0)
						file << setw(3) << " ";

					if (draw == 1)
						file << setw(3) << "#";
					//////////////////////////////////////////////////////////////////////////////////
				}
				file << endl;
			}
			file << endl << endl;

		}

		file.close();
	}
	
	void Bot::load2(Player& p)
	{
		fstream file;
		if (file.good())
		{
			
			int draw;
			file.open("log.txt", ios::out | ios::app);
			file << "Flota komputera po bitwie: " << endl;
			file << endl << " ";
			for (int i = 0; i < 10; i++)
				file << setw(3) << i;
			file << endl;

			for (int i = 0; i < 10; i++)
			{
				file << (char)(65 + i);
				////////////////////////////////////////////////////////////////////////////////
				for (int j = 0; j < 10; j++)
				{
					draw = 0;

					for (int s = 0; s < m_ships.size(); s++)
					{
						for (int p = 0; p < (*m_ships[s]).getParts().size(); p++)
						{
							if ((*(*m_ships[s]).getParts()[p]).getX() == j && (*(*m_ships[s]).getParts()[p]).getY() == i)
								draw = 4;

						}
					}

					for (int k = 0; k < p.getShots().size(); k++)
					{
						if (p.getShots()[k].getX() == j && p.getShots()[k].getY() == i)
						{
							draw = 1;

							

							if (p.getShots()[k].getHit() == 1)  // jesli trafienie
								draw = 2;
							if (p.getShots()[k].getHit() == 2)  // jesli zatopienie
								draw = 3;

							break;
						}

					}
					if (draw == 0)
						file << setw(3) << " ";

					else if (draw == 1)
						file << setw(3) << ".";

					else if (draw == 4)
						file << setw(3) << "#";

					else if (draw == 2)
						file << setw(3) << "!";

					else if (draw == 3)
						file << setw(3) << "X";
					


					//////////////////////////////////////////////////////////////////////////////////
				}
				file << endl;
			}
			file << endl << endl;
		}
		file.close();
	}