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

	bool isDead = false;

	// ----- MAX VALUES -----

	int maxAgility;
	int maxHealth;
	int maxStamina;
	int maxPotion = MAX_POTION;

};

void InitializePlayer(Player* player);