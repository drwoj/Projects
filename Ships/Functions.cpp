#include "Functions.h"

void menu(Player& p, Bot& b, Leaderboard& l)
{
	bool dalej = true;;
	char wybor;
	cout << "Witaj w grze statki !" << endl;
	Sleep(1);
	while (dalej)
	{
		cout << "Wybierz opcje: " << endl << "1. Graj" << endl << "2. Zasady" << endl << "3. Tabela Liderow" << endl << endl;
		wybor = _getch();
		switch (wybor)
		{
		case'1':
			system("cls");
			dalej = false;
			cout << "Podaj swoj nick: ";
			p.setNick();
			system("CLS");
			p.display(b);
			break;

		case '2':
			system("cls");
			cout << "Rozgrywka toczy sie z inteligentym botem.\nKazdy z graczy dysponuje odpowiednio:\n1 statkiem 4 masztowym\n2 - 3\n3 - 2\n4 - 1\n\nStatki nie moga do siebie przylegac, nawet na ukos.\nDlatego po zatopieniu statku, zostanie on obrysowany.\nStrzaly Sa oddawane rownoczesnie. Nalezy podac odpowiednie wspolrzedne.\nRozgrywka konczy sie, gdy ktorys z graczy zatopi cala flote rywala." << endl << endl << endl;
			break;

		case '3':
			system("cls");
			l.show();
			cout << endl << endl;
			break;

		default:
			system("cls");
			cout << "Wybrano zla opcja!" << endl;

		}
	}
}

void set(Player& p, Bot& b)
{
	p.where(1, b);
	p.where(1, b);
	p.where(1, b);
	p.where(1, b);
	p.where(2, b);
	p.where(2, b);
	p.where(2, b);
	p.where(3, b);
	p.where(3, b);
	p.where(4, b);
	//////////////////

}

void setb(Bot& b)
{
	b.where(1, b);
	b.where(1, b);
	b.where(1, b);
	b.where(1, b);

	b.where(2, b);
	b.where(2, b);
	b.where(2, b);

	b.where(3, b);
	b.where(3, b);

	b.where(4, b);
}

void setp(Player& p)
{
	p.addShip(0, 0, 1, 1);
	p.addShip(0, 2, 1, 1);
	p.addShip(0, 4, 1, 1);
	p.addShip(0, 6, 1, 1);

	p.addShip(0, 8, 2, 0);
	p.addShip(7, 7, 2, 0);
	p.addShip(3, 2, 2, 1);

	p.addShip(3, 6, 3, 1);
	p.addShip(7, 2, 3, 0);

	p.addShip(5, 5, 4, 0);
}

void battle(Player& p, Bot& b)
{
	vector<User*> v;

	v.push_back(&p);
	v.push_back(&b);


	bool end = false;

	while (true)
	{
		//cout << "Twoja Flota: " << endl << endl;
		p.display(b);
		//cout << endl << endl << endl << "Flota Przeciwnika: " << endl << endl;
		b.display(p, b);
		p.shot_coords();
		p.shot(b);
		b.coords(p);
		b.shot(p);
		Sleep(1500);
		system("CLS");

		//cout << "flota gracza: " << p.getShips().size() << endl;
		//cout << "flota komputera: " << b.getShips().size()<<endl;

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i]->stop())
			{
				//cout << "WESZ£O W IF" << endl;
				end = true;
				p.display(b);
				b.display(p, b);
				v[0] = nullptr;
				v[1] = nullptr;
				delete v[0];
				delete v[1];
				break;
			}
		}
		if (end)
			break;
	}
}

void shots(Player& p, Bot& b)
{
	fstream file;
	file.open("Log.txt", ios::out | ios::app);

	if (file.good())
	{
		file << endl << "Strzaly oddane przez gracza: " << endl;
		p.shots();
		file << endl << "Strzaly oddane przez komputer: " << endl;
		b.shots();
	}
	file.close();

}