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
	map->numChests = 2;
	for (int i = 0; i < map->numChests; i++) {
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

	std::cout << "--------------- D U N G E O N ---------------" << std::endl;
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

	system("cls");

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

		if (player.agility > 0) {
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

			// Obtener la posición y valor de la casilla actual de Player
			char currentValue = ' ';
			for (Enemy e : listEnemies) {
				if (player.playerPosition.x == e.enemyPosition.x && player.playerPosition.y == e.enemyPosition.y) {
					currentValue = 'E';

					break;
				}
			}
			if (currentValue != 'E') {
				for (Chest c : listChests) {
					if (player.playerPosition.x == c.chestPosition.x && player.playerPosition.y == c.chestPosition.y) {
						currentValue = 'C';
						break;
					}
				}
			}	

			// Si coincide casilla entonces
			if (currentValue == 'E') {
				Combat();
				currentValue == ' ';
			}
			else if (currentValue == 'C') {
				OpenChest();
			}
			else {
				return;
			}

		}
		else //If Player's Agility falls to 0, Enemies move again around the map
		{
			player.agility = player.maxAgility;
			EnemyMovement();
		}
		return Dungeon();
	}
	

}

void OpenChest() {
	system("cls");
	Chest c;
	Player p;

	if (!c.isLooted)
	{
		std::cout << "------ CHEST ------" << std::endl;
		std::cout << "\n > You open the chest and it contains: " << std::endl;
		std::cout << "\n\t> " << c.gold << " gold!" << std::endl;
		std::cout << "\t> Also you got the wonderful " << c.gear.nameGear << std::endl;
		std::cout << std::endl;

		if (c.ContainsPotion)
		{
			if (p.potion >= p.maxPotion)
				std::cout << "\t\t> You already have max amount of potions!" << std::endl;
			else
				std::cout << "\t> You got a potion!" << std::endl;
				p.potion++;
		}

		std::cout << "\n______________________________________\n" << std::endl;
		c.isLooted = true;
		system("pause");
	}
}

void Map::PrintBar(char fill, int value, int maxValue) {
	int barSize = 10;
	int printBars = ((float)value / (float)maxValue) * 10.0f;
	if (value != 0) {
		printBars = std::max(1, printBars);
	}

	std::cout << "[";

	for (int i = 0; i < barSize; i++) {
		if (i < printBars) {
			std::cout << fill;
		}
		else {
			std::cout << " ";
		}
	}

	std::cout << "] ";
}

int Map::EnemyAction() {
	Enemy* e = new Enemy;

	if (e->health < e->maxHealth * 0.3f && e->stamina < e->maxStamina * 0.3f) {
		return 0;
	}
	if (e->stamina < e->maxStamina * 0.2f) {
		return 1;
	}
	return 2;
}

void Map::Combat() {
	char action;
	Enemy* e = new Enemy;
	Player p;
	int amountBet;
	int eAttack = (20 + (rand() % (e->stamina - 20))) + 1;

	while (!p.isDead && !e->isDead) {
		std::system("cls");
		std::cout << "------ COMBAT ------\n" << std::endl;
		std::cout << "-- " << "Enemy" << " --" << std::endl;
		PrintBar('=', e->health, e->maxHealth);
		std::cout << " ? HP" << std::endl;
		PrintBar('>', e->stamina, e->maxStamina);
		std::cout << " ? Stamina\n" << std::endl;
		std::cout << "-----------------\n" << std::endl;
		std::cout << "-- Player --" << std::endl;
		PrintBar('=', player.health, player.maxHealth);
		std::cout << " " << player.health << " / " << player.maxHealth << " HP" << std::endl;
		PrintBar('>', player.stamina, player.maxStamina);
		std::cout << " " << player.stamina << " / " << player.maxStamina << " Stamina\n" << std::endl;
		std::cout << "Potions " << player.potion << " / " << player.maxPotion << "\n" << std::endl;
		std::cout << "______________________________________\n" << std::endl;
		std::cout << "A -> Attack" << std::endl;
		std::cout << "D -> Defend" << std::endl;
		std::cout << "R -> Rest" << std::endl;
		std::cout << "P -> Potion\n" << std::endl;
		std::cout << "Enter your action: ";
		std::cin >> action;
		std::cout << std::endl;

		int eAction = EnemyAction();

		if (action == 'A' || action == 'a') {
			std::cout << "Enter the attack value " << "(Max " << player.maxStamina << "): ";
			std::cin >> amountBet;
			std::cout << std::endl;
			switch (eAction) {
			case 2:
				if (player.stamina > e->stamina) {
					e->health -= amountBet;
					e->stamina -= e->stamina;
					player.stamina -= amountBet;
					if (player.stamina < 0) {
						player.stamina = 0;
					}
					if (e->stamina < 0) {
						e->stamina = 0;
					}
					std::cout << "You strike the enemy with more force! The enemy receives " << amountBet << " damage" << std::endl;
				}
				else {
					player.health -= eAttack;
					e->stamina -= eAttack;
					player.stamina -= amountBet;
					if (player.stamina < 0) {
						player.stamina = 0;
					}
					if (e->stamina < 0) {
						e->stamina = 0;
					}
					std::cout << "The enemy strikes with more force! You receive " << eAttack << " damage" << std::endl;
				}
				system("pause");
				system("cls");
				//IfWin();
				//IfLose(enemy);
				break;
			case 0:
				e->health -= amountBet * 0.25f;
				e->stamina += e->maxStamina * 0.25f;
				player.stamina -= amountBet;
				if (player.stamina < 0) {
					player.stamina = 0;
				}
				if (e->stamina > e->maxStamina) {
					e->stamina = e->maxStamina;
				}
				std::cout << "The enemy defends, but receives " << amountBet << " damage\n" << std::endl;
				break;
			case 1:
				e->health -= amountBet;
				e->stamina = e->maxStamina;
				player.stamina -= amountBet;
				std::cout << "You strike the unprepared enemy dealing " << amountBet << " damage!\n" << std::endl;
				break;
			}
		}
		else if (action == 'D' || action == 'd') {
			switch (eAction) {
			case 2:
				player.health -= eAttack * 0.25f;
				e->stamina -= eAttack;
				if (e->stamina < 0) {
					e->stamina = 0;
				}
				std::cout << "You defend the enemy's blow, but receive " << eAttack << " damage\n" << std::endl;
				break;
			case 0:
				e->stamina += e->maxStamina * 0.25f;
				if (e->stamina > e->maxStamina) {
					e->stamina = e->maxStamina;
				}
				std::cout << "You both defended yourselves...\n" << std::endl;
				break;
			case 1:
				e->stamina = e->maxStamina;
				std::cout << "You defend while the enemy catches a breath! It seems ready to strike!\n" << std::endl;
				break;
			}
			player.stamina += player.maxStamina * 0.25f;
			if (player.stamina > player.maxStamina) {
				player.stamina = player.maxStamina;
			}
		}
		else if (action == 'R' || action == 'r') {
			player.stamina = player.maxStamina;
		}
		else if ((action == 'P' || action == 'p') && player.potion > 0) {
			if (player.potion <= 0) {
				std::cout << "You have no potions" << std::endl;
			}
			else {
				std::cout << "You drink the potion when the enemy hits you, striking for " << eAttack << " damage" << std::endl;
				player.health += player.maxHealth * 0.4f;
				player.potion--;
			}
		}
	}
}

void Map::EnemyMovement() {
	for (int i = 0; i < numEnemies; i++) {
		int randomDirection = GenerateClampedRandom(0, 3);
		// Random enemy position again
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
	return Dungeon();
}