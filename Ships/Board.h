#pragma once
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <conio.h>
#include<windows.h>
#include<vector>
#include<memory>
#include "Player.h"
#include "Bot.h"
using namespace std;

class Board
{
public:
	void display(Player& p, Bot& b);
	
};