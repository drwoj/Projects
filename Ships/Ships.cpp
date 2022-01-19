#include "Header.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Player p;
	Bot b;
	Leaderboard l;

	l.getLeaders();
	menu(p,b,l);
	set(p,b);
	setb(b);
	p.load1();
	b.load1();

	system("cls");
	battle(p, b);

	p.load2(b);
	b.load2(p);
	shots(p, b);

	p.score(b);	
	l.check(p);
	cout << endl << endl << "TWOJ WYNIK: " << p.getScore()<<endl<<endl<<endl;
}