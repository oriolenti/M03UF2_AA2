#pragma once
#pragma once

#include <iostream>
#include "map.h"

struct Enemy {

	MapPosition enemyPosition;

	bool isDead;

	int health;
	int maxHealth;

	int stamina;
	int maxStamina;
};


void InitializeEnemy(Enemy* e, MapPosition* enemyPosition);