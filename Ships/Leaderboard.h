#pragma once
#include "Leader.h"
#include "Player.h"
#include <vector>
#include <memory>
#include <fstream>

using namespace std;
class Leaderboard
{
	vector<shared_ptr<Leader>> m_leaders;


public:
	void getLeaders();
	void check(Player& p);
	void show();
	void load();
	void sort();
	void swap(Leader &l1, Leader &l2);


};

