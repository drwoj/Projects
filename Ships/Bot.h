#pragma once
#include "User.h"

using namespace std;
class Player;

class Bot : public User
{
	bool target = false;
	int m_x;
	int m_y;
	bool wasHit = false;
	int last;
	bool left = true;
	bool right = true;
	bool up = true;
	bool down = true;
	int counter;
	bool horizontal;
	int m_hp = 10;

public:

	void where(int size, Bot &b);

	void coords(Player &p);

	bool shot(Player &p);

	bool stop();

	void dmg();
	
	int getHp();

	void display(Player &p, Bot& b);

	void load1();
	
	void load2(Player &p);
	
};




