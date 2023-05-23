#include "MainManager.h"


void InitGame(Map* map) {
	// ----------------- AUX VARIABLES ------------------
	MapPosition auxPosition;
	bool valid;
	// --------------------- GEARS ----------------------
	Gear allGears[10];
	InitGears(allGears); // TODO


	// --------------------- PLAYER ----------------------
	InitializePlayer(&map->player);

	// --------------------- ENEMIES ----------------------
	//Set the number of enemies between 5 and 7
	map->numEnemies = GenerateClampedRandom(5, 7);
	for (int i = 0; i < map->numEnemies; i++) {
		do {
			valid = true;
			auxPosition.x = GenerateClampedRandom(0, MAP_SIZE - 1);
			auxPosition.y = GenerateClampedRandom(0, MAP_SIZE - 1);
			valid = !CheckIfPositionsAreEqual(&auxPosition, &map->player.playerPosition);
			for (int j = 0; j < i && valid; j++) {
				valid = !CheckIfPositionsAreEqual(&auxPosition, &map->listEnemies[j].enemyPosition);
			}
		} while (!valid);

		InitializeEnemy(&map->listEnemies[i], &auxPosition);
	}
	// --------------------- CHEST ----------------------
	//initialize chests
	for (int i = 0; i < 2; i++) {
		do {
			valid = true;
			//e->position.x = 3;
			auxPosition.x = GenerateClampedRandom(0, MAP_SIZE - 1);
			auxPosition.y = GenerateClampedRandom(0, MAP_SIZE - 1);
			//e->position.y = 2;
			valid = !CheckIfPositionsAreEqual(&auxPosition, &map->player.playerPosition);
			for (int j = 0; j < i && valid; j++) {
				valid = !CheckIfPositionsAreEqual(&auxPosition, &map->listChests[j].chestPosition);
			}
			for (int j = 0; j < map->numEnemies && valid; j++) {
				valid = !CheckIfPositionsAreEqual(&auxPosition, &map->listEnemies[j].enemyPosition);
			}
		} while (!valid);

		InitializeChest(&map->listChests[i], allGears, &auxPosition);
	}
}

void Map::Dungeon() {
	std::cout << " --------------- D U N G E O N ---------------" << std::endl;
	std::cout << std::endl;
	std::cout << " E -> Enemy	P -> Player	C -> Chest" << std::endl;
	std::cout << std::endl;
	std::cout << " Health: " << player.health << " / " << player.maxHealth << std::endl;
	std::cout << " Potions: " << player.potion << " / " << MAX_POTION << std::endl;
	std::cout << " Moves: " << player.agility << " / " << player.maxAgility << std::endl;

	for (int k = 0; k < 1; k++) {
		std::cout << " ";

		for (int i = 0; i < MAP_SIZE; i++) {
			std::cout << " ___ ";
		}
		std::cout << std::endl;

		for (int i = 0; i < MAP_SIZE; i++) {
			std::cout << " ";

			for (int j = 0; j < MAP_SIZE; j++) {
				std::cout << "|   |";
			}
			std::cout << std::endl;
			std::cout << " ";

			for (int j = 0; j < MAP_SIZE; j++) {
				char value = ' ';
				if (player.playerPosition.y == j && player.playerPosition.x == i) {
					value = 'P';
				}
				for (Enemy e : listEnemies) {
					if (e.enemyPosition.y == j && e.enemyPosition.x == i) {
						value = 'E';
					}
				}
				for (Chest c : listChests) {
					if (c.chestPosition.y == j && c.chestPosition.x == i) {
						value = 'C';
					}
				}

				std::cout << "| " << value << " |";
			}

			std::cout << std::endl;
			std::cout << " ";

			for (int j = 0; j < MAP_SIZE; j++) {
				std::cout << "|___|";
			}
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;
	std::cout << " ---------------------------------------------" << std::endl;
	std::cout << std::endl;
	std::cout << " W A S D -> Movement" << std::endl;
	std::cout << " P -> Potion" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	char action;
	std::cout << " Enter your action: ";
	std::cin >> action;
	bool gameOver = false;

	//Valid Actions
	while (!gameOver) {

		if (player.agility > 1) {
			if (action == 'W')
			{
				if (player.playerPosition.x - 1 < 0) {
					// cant move that way
					std::cout << "Invalid position" << std::endl;
					system("pause");
				}
				else {
					player.agility--;
					player.playerPosition.x--;
				}

			}
			else if (action == 'S')
			{
				if (player.playerPosition.x + 1 >= MAP_SIZE) {
					// cant move that way
					std::cout << "Invalid position" << std::endl;
					system("pause");
				}
				else {
					player.agility--;
					player.playerPosition.x++;
				}
			}
			else if (action == 'A')
			{
				if (player.playerPosition.y - 1 < 0) {
					// cant move that way
					std::cout << "Invalid position" << std::endl;
					system("pause");
				}
				else {
					player.agility--;
					player.playerPosition.y--;
				}
			}
			else if (action == 'D')
			{
				if (player.playerPosition.y + 1 >= MAP_SIZE) {
					// cant move that way
					std::cout << "Invalid position" << std::endl;
					system("pause");
				}
				else {
					player.agility--;
					player.playerPosition.y++;
				}
			}

			else if (action == 'P')
			{
				if (player.potion >= 1)
				{

					//Healing more than maxHealth = Full Heal
					if ((player.health + (player.health * 0, 4)) >= player.maxHealth)
					{
						player.agility--;
						player.potion--;
						player.health = player.maxHealth;
						std::cout << "You fully healed!" << std::endl;
					}
					//Else Heal 40%
					else
					{
						player.agility--;
						std::cout << "You healed " << (player.health * 0, 4) << "HP" << std::endl;
						player.potion--;
						player.health = (player.health + (player.health * 0, 4));


					}
				}
				else
				{
					std::cout << "You don't have any potions!" << std::endl;
					system("clear");
				}
			}
			else
			{
				std::cout << "Invalid command, enter a new one" << std::endl;
				system("pause");
				//system("clear");
			}
			Dungeon();
		}
		else //If Player's Agility falls to 0, Enemies move again around the map
		{
			EnemyMovement();
		}
	}
}

void Map::EnemyMovement() {
	for (int i = 0; i < numEnemies; i++) {
		int randomDirection = GenerateClampedRandom(0, 3);

		// Mover el enemigo en la dirección aleatoria
		if (randomDirection == 0 && listEnemies[i].enemyPosition.x - 1 >= 0) {
			listEnemies[i].enemyPosition.x--;
		}
		else if (randomDirection == 1 && listEnemies[i].enemyPosition.x + 1 < MAP_SIZE) {
			listEnemies[i].enemyPosition.x++;
		}
		else if (randomDirection == 2 && listEnemies[i].enemyPosition.y - 1 >= 0) {
			listEnemies[i].enemyPosition.y--;
		}
		else if (randomDirection == 3 && listEnemies[i].enemyPosition.y + 1 < MAP_SIZE) {
			listEnemies[i].enemyPosition.y++;
		}
	}
}