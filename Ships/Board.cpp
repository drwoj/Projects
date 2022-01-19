#include "Board.h"



	void Board::display(Player& p, Bot& b)
	{
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
