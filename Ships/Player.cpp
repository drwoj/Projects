#include "Player.h"
#include "Bot.h"
	void Player::shot_coords()
	{
		string s;
		char a;
		char b;

		while (true)
		{
			cout << endl << endl << "Podaj wspolrzedne strzalu (np. A5 - zwroc uwage na drukowane litery): ";

			cin >> s;
			if (s.length() != 2)
			{
				cout << endl << "Podaj dwie Wspolrzedne!" << endl;
				Sleep(1500);
				continue;
			}

			a = s[0];
			b = s[1];

			if (((b >= '0') && (b <= '9')) && ((a >= 'A') && (a <= 'J')))
			{
				m_x = b - 48;
				m_y = a - 65;
				break;
			}
			else
			{
				cout << endl << "Podano bledne wspolrzedne!" << endl;
				Sleep(1500);
				continue;
			}
		}

	}

	bool Player::shot(Bot& b)
	{
		for (int i = 0; i < b.getShips().size(); i++)
		{
			for (int j = 0; j < (*b.getShips()[i]).getParts().size(); j++)
			{
				if ((*(*b.getShips()[i]).getParts()[j]).getX() == m_x && (*(*b.getShips()[i]).getParts()[j]).getY() == m_y)
				{
					//cout << endl << "Size przed: " << (*b.getShips()[i]).getParts().size() << endl;
					(*(*b.getShips()[i]).getParts()[j]).damage();
					//cout << endl << "Size po " << (*b.getShips()[i]).getParts().size() << endl;
					cout << endl << "TRAFIENIE! " << endl;

					if ((*b.getShips()[i]).sink())
					{
						b.dmg();
						int size = (*b.getShips()[i]).getSize();

						for (int k = 0; k < size; k++)
							for (int l = 0; l < m_bullets.size(); l++)
								if ((*m_bullets[l]).getX() == (*(*b.getShips()[i]).getParts()[k]).getX() && (*m_bullets[l]).getY() == (*(*b.getShips()[i]).getParts()[k]).getY())
								{
									(*m_bullets[l]).allHit();

									break;
								}
						addBullet(m_x, m_y, 2);
						addShot(m_x, m_y, 2);


						int y = (*b.getShips()[i]).getY();
						int x = (*b.getShips()[i]).getX();

						if ((*b.getShips()[i]).getOrientation())
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


						b.alive(i);
					}
					else
					{
						addShot(m_x, m_y, 1);
						addBullet(m_x, m_y, 1);
					}

					return true;
				}
			}
		}
		cout << endl << "Pudlo! " << endl;
		addShot(m_x, m_y, 0);
		addBullet(m_x, m_y, 0);
		return false;
	}

	void Player::display(Bot &b)
	{
		cout << endl << "Twoja Flota: " << endl;
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
				int draw = 0;
				for (int s = 0; s < m_ships.size(); s++)
				{
					for (int p = 0; p < (*m_ships[s]).getParts().size(); p++)
					{
						if ((*(*m_ships[s]).getParts()[p]).getX() == j && (*(*m_ships[s]).getParts()[p]).getY() == i)
							draw = 1;

					


					}
				}
				for (int k = 0; k < b.getBullets().size(); k++)
				{
					if ((*b.getBullets()[k]).getX() == j && (*b.getBullets()[k]).getY() == i)
					{
						draw = 2;

						if ((*b.getBullets()[k]).getHit() == 1)  // jesli trafienie
							draw = 3;
						if ((*b.getBullets()[k]).getHit() == 2)  // jesli zatopienie
							draw = 4;

						break;
					}

				}


				if (draw == 0)
					cout << setw(3) << ".";

				if (draw == 1)
					cout << setw(3) << "#";				

				if (draw == 2)
					cout << setw(3) << " ";

				if (draw == 3)
					cout << setw(3) << "!";

				if (draw == 4)
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
	};

	void Player::where(int size, Bot &bot)
	{
		bool orientation = false;
		char a;
		char b;
		string s;
		system("cls");
		display(bot);

		while (true)
		{
			cout << endl << endl << "Ustawiasz statek: " << size << " masztowy." << endl << endl << "Podaj wspolrzedna (np. A7 - zwroc uwage na drukowane litery)\n(potem podasz orientacje, statek rysowany jest w prawo lub w dol): ";
			cin >> s;

			if (s.length() != 2)
			{
				cout << endl << "Podano bledne wspolrzedne! " << endl;
				Sleep(1500);
				system("cls");
				display(bot);
				continue;

			}

			a = s[0];
			b = s[1];


			if (((b >= '0') && (b <= '9')) && ((a >= 'A') && (a <= 'J')))
			{
				if (b - 48 + size > 10 && a - 65 + size > 10)
				{
					cout << endl << "Statek sie tu nie zmiesci!" << endl;;
					continue;
				}

				if (size > 1)
					while (true)
					{
						cout << endl << "Podaj orientacje statku (1. - poziomo / 2. - pionowo): ";
						cin >> s;
						if (s.length() != 1)
						{
							cout << endl << "Wybrano zla opcje! Wybierz jeszcze raz" << endl;
							Sleep(1500);
							system("CLS");
							display(bot);
							continue;
						}

						if (s[0] == '1')
						{
							if (b - 48 + size > 10)
							{
								cout << endl << "W ten sposob statek sie nie zmiesci!" << endl;
								Sleep(1500);
								system("CLS");
								display(bot);
								continue;
							}
							orientation = false;
							break;
						}

						if (s[0] == '2')
						{
							if (a - 65 + size > 10)
							{
								cout << endl << "W ten sposob statek sie nie zmiesci!" << endl;
								Sleep(1500);
								system("CLS");
								display(bot);
								continue;
							}
							orientation = true;
							break;
						}

					}
			}

			else
			{
				cout << endl << "Podano bledne wspolrzedne!" << endl;
				Sleep(1500);
				system("CLS");
				display(bot);
				continue;
			}

			if (collision(b - 48, a - 65, size, orientation))
			{
				cout << endl << "Statki nie moga do siebie przylegac!" << endl;
				Sleep(1500);
				system("CLS");
				display(bot);
				continue;
			}
			break;
		}

		cout << endl << "Ustawiono statek !" << endl;
		addShip(b - 48, a - 65, size, orientation);
		Sleep(1000);
	}

	bool Player::stop()
	{
		cout << "Twoje Zycie: " << m_hp << endl;
		
			if (m_hp==0)
			{
				cout << endl << "KONIEC GRY!" << endl << "PRZECIWNIK ZWYCIEZYL! " << endl;
				return true;
			}
			return false;
		
	}

	void Player::dmg()
	{
		m_hp--;
	}

	int Player::getHp()
	{
		return m_hp;
	}

	void Player::load1()
	{
		fstream file;
		file.open("log.txt", ios::out | ios::app);
		if (file.good())
		{
			file << "==================================" << endl;
			file << "Poczatkowe ustawienie gracza "<<m_nick <<" "<< endl;

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

	void Player::load2(Bot& b)
	{
		fstream file;
		file.open("log.txt", ios::out | ios::app);
		if (file.good())
		{	
			file << "flota gracza " << m_nick <<" po bitwie: "<< endl;

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
					int draw = 0;
					for (int s = 0; s < m_ships.size(); s++)
					{
						for (int p = 0; p < (*m_ships[s]).getParts().size(); p++)
						{
							if ((*(*m_ships[s]).getParts()[p]).getX() == j && (*(*m_ships[s]).getParts()[p]).getY() == i)
								draw = 1;




						}
					}
					for (int k = 0; k < b.getShots().size(); k++)
					{
						if (b.getShots()[k].getX() == j && b.getShots()[k].getY() == i)
						{
							draw = 2;

							if (b.getShots()[k].getHit() == 1)  // jesli trafienie
								draw = 3;
							if (b.getShots()[k].getHit() == 2)  // jesli zatopienie
								draw = 4;

							break;
						}

					}


					if (draw == 0)
						file << setw(3) << " ";

					if (draw == 1)
						file << setw(3) << "#";

					if (draw == 2)
						file << setw(3) << ".";

					if (draw == 3)
						file << setw(3) << "!";

					if (draw == 4)
						file << setw(3) << "X";


					//////////////////////////////////////////////////////////////////////////////////
				}
				file << endl;
			}
			file << endl<<endl;
			
		}
		
		file.close();
			
	}

	int Player::score(Bot& b)
	{
		m_score = (5 * m_hp + 5) / (b.getHp() + 1);
		return m_score;
	}


	int Player::getScore()
	{
		return m_score;
	}

	string Player::getNick()
	{
		return m_nick;
	}