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
	
	void Combat(Player* p, Enemy* e);
	void PrintBar(char fillCharacter, int value, int maxValue);
	int EnemyAction(Enemy* e);
	
	void OpenChest(Player* p, Chest* c);

	void GameOver(Player* p);
};

enum Scene { MENU, DUNGEON, COMBAT, CHEST, GAMEOVER };
void InitGame(Map* map);