#pragma once
#include"ShipPart.h"
using namespace std;

class Ship
{
	int m_x;
	int m_y;
	int m_size;
	bool m_vertical;
	vector<shared_ptr<ShipPart>> parts;

public:
	vector<shared_ptr<ShipPart>> getParts();


		Ship(int x, int y, int size, bool vertical);

		bool sink();


		int getSize();

		bool getOrientation();


		int getX();


		int getY();

};
