#pragma once
#include <iostream>
using namespace std;

class Bullet
{
	int m_x;
	int m_y;
	int m_hit;

public:
	int getX();

	int getY();

	void allHit();

	int getHit();

	Bullet(int x, int y, int hit);

	friend ostream& operator<< (ostream& out, const Bullet& bullet);

};



