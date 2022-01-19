#pragma once
#include<vector>
#include<memory>
using namespace std;

class ShipPart
{
	int m_x;
	int m_y;
	bool m_alive;

public:
	ShipPart(int x, int y, bool alive);

	int getX();
	

	int getY();
	

	void damage();


	bool isAlive();


};

