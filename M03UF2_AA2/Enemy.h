#pragma once
#pragma once

#include <iostream>
#include "map.h"

struct Enemy {

	MapPosition enemyPosition;

	bool isDead;

	int health;

	int stamina;
};


void InitializeEnemy(Enemy* e, MapPosition* enemyPosition);