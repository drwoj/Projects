#pragma once
#include <iomanip>
#include<windows.h>
#include<vector>
#include<memory>
#include<fstream>
#include "Ship.h"
#include "Bullet.h"
using namespace std;

class User
{
protected:
	int m_x;
	int m_y;
	vector<shared_ptr<Ship>> m_ships;
	vector<shared_ptr<Bullet>> m_bullets;
	vector<Bullet> m_shots;

public:

	void addBullet(int x, int y, int hit);

	void addShot(int x, int y, int hit);

	vector<Bullet> getShots();

		vector<shared_ptr<Bullet>> getBullets();


		void addShip(int x, int y, int size, bool horizontal);


		vector<shared_ptr<Ship>> getShips();


		void alive(int i);


		bool collision(int x, int y, int size, bool orientation);

		virtual bool stop() =0; 
		//void where(int size, Bot& b);
		
		void shots();

};
