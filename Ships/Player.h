#pragma once
//#include <iostream>
//#include <stdio.h>
//#include <cstdlib>
//#include <iomanip>
//#include <conio.h>
//#include<windows.h>
//#include<vector>
//#include<memory>
#include "User.h"
#include "Bot.h"

using namespace std;



class Player : public User
{
	int m_hp = 10;
	int m_score;
	string m_nick="drwoj";


	
public:

	void shot_coords();

	bool shot(Bot& b);

	void display(Bot &bot);

	void where(int size, Bot& b);

	bool stop();

	void dmg();

	int getHp();

	void load2(Bot &b);

	void load1();

	int score(Bot &b);

	void setNick()
	{
		cin >> m_nick;
	}

	int getScore();

	string getNick();
};


