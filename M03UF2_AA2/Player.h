#pragma once

#include <iostream>

#include"map.h"

#define MAX_POTION 3

struct Player {

	MapPosition playerPosition;

	// ----- CURRENT VALUES -----

	int gold;
	int health;
	int stamina;
	int agility;
	int potion;

	// ----- MAX VALUES -----

	int maxAgility;
	int maxHealth;
	int maxStamina;

};

void InitializePlayer(Player* player);