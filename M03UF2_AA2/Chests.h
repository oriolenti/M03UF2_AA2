#pragma once

#include <string>

#include "map.h"
#include "Player.h"

struct Gear {

	std::string nameGear;
	std::string descrptionGear;

	int value;
	int health;
	int stamina;
	int agility;

};

const Gear gear[10]{
	Gear{ "Under Crown", "Crown of the underworld empire", 200, 20, 40, 1 },
		Gear{ "MILF Flops", "Harder than steel, boomer than a boomerang", 10, -10, -5, 1 },
		Gear{ "White Spice", "It's use is undefined, tastes funny", 150, -20, 20, 1 },
		Gear{ "Pretender Crown", "From a long time ago crown pretender" - 300, -20, -40, -1 },
		Gear{ "Super Stretchy Leggings", "'They say ''Juicy''", 50, -10, 0, 2 },
		Gear{ "Life Goals", "A light at the end of the tunnel", 170, 30, 0, 0 },
		Gear{ "Spaghettoni", "Mom'spaghetti best spaghetti", 10, 5, 0, 0 },
		Gear{ "Tribal Mask", "Cursed mask from deep jungle tribes", 25, 10, 0, 0 },
		Gear{ "Furry Gloves", "Because why not hate yourself even more", -50, 0, -10, 0 },
		Gear{ "Latex Boots", "You dont waer those because they're comfy", 69, 0, 7, 0 }
};

struct Chest {

	MapPosition chestPosition;

	int gold;

	bool isLooted;

	Gear gear;

	bool ContainsPotion;

};

void InitializeChest(Chest* chest, MapPosition* chestPosition);
void InitGears(Gear allGears[10]); 