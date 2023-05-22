#pragma once

#include <string>

#include "map.h"
#include "Player.h"

struct Gear {

	int value;

	std::string nameGear;

	int health;
	int stamina;
	int agility;

};

struct Chest {

	MapPosition chestPosition;

	int gold;

	bool isLooted;

	Gear gear;

	bool ContainsPotion;

};

void InitializeChest(Chest* chest, Gear allGears[10], MapPosition* chestPosition);
void InitGears(Gear allGears[10]); // TODO