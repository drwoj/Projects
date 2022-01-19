#include "Ship.h"


vector<shared_ptr<ShipPart>> Ship::getParts()
{
	return parts;
}

Ship::Ship(int x, int y, int size, bool vertical) : m_x{ x }, m_y{ y }, m_size{ size }, m_vertical{ vertical }
{
	for (int i = 0; i < size; i++)
	{
		if (!vertical)
			parts.push_back(make_shared<ShipPart>(x + i, y, true));
		else
			parts.push_back(make_shared<ShipPart>(x, y + i, true));

	}
}

bool Ship::sink()
{
	for (int i = 0; i < parts.size(); i++)
		if ((*parts[i]).isAlive())
			return false;
	return true;
}

int Ship::getSize()
{
	return m_size;
}

bool Ship::getOrientation()
{
	return m_vertical;
}

int Ship::getX()
{
	return m_x;
}

int Ship::getY()
{
	return m_y;
}