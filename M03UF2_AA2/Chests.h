#pragma once

#include <string>

#include "map.h"
#include "Player.h"

struct Gear {

	std::string nameGear;
	std::string descriptionGear;

	int value;
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
void InitGears(Gear allGears[10]); 