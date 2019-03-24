#include "pch.h"

#ifndef SEA_BATTLE_H
#define SEA_BATTLE_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class Player {
public:
	int zones[10][10];
	int ships;
	int ships_hp[10];

};

bool is_alive(Player a);

#endif