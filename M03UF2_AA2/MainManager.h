#pragma once

#include "map.h"
#include "Enemy.h"
#include "Player.h"
#include "Chests.h"

struct Map {

	int numEnemies;

	Enemy listEnemies[7];
	Chest listChests[2];
	Player player;
	void Dungeon();

};

enum Scene { MENU, DUNGEON, COMBAT, CHEST, GAMEOVER };
void InitGame(Map* map);
