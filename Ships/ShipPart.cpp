#include "ShipPart.h"


ShipPart::ShipPart(int x, int y, bool alive = true) : m_x{ x }, m_y{ y }, m_alive{ alive } {}

int ShipPart::getX()
{
	return m_x;
}

int ShipPart :: getY()
{
	return m_y;
}

void ShipPart :: damage()
{
	m_alive = false;
}

bool ShipPart :: isAlive()
{
	return m_alive;
}