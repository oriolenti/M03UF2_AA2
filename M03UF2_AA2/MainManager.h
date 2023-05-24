#pragma once

#include "map.h"
#include "Enemy.h"
#include "Player.h"
#include "Chests.h"

#include <iostream>
#include <cstdlib>

struct Map {

	int numEnemies;
	int numChests;

	Enemy listEnemies[7];
	Chest listChests[2];
	Player player;

	void Dungeon();
	void EnemyMovement();
	
	void Combat();
	void PrintBar(char fillCharacter, int value, int maxValue);
	int EnemyAction();
	
	void OpenChest();
};

enum Scene { MENU, DUNGEON, COMBAT, CHEST, GAMEOVER };
void InitGame(Map* map);