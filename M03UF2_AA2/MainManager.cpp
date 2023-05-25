#include "MainManager.h"


void InitGame(Map* map) {
	// ----------------- AUX VARIABLES ------------------
	MapPosition auxPosition;
	bool valid;
	// --------------------- GEARS ---------------------- // TODO


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

		Enemy* e = new Enemy;
		map->listEnemies[i] = *e;

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


		Chest* c = new Chest;
		map->listChests[i] = *c;

		InitializeChest(&map->listChests[i], &auxPosition);
	}
}

void Map::Dungeon() {

	bool gameOver = false;

	//Valid Actions
	while (!gameOver) {

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
						if (e.enemyPosition.y == j && e.enemyPosition.x == i && !e.isDead) {
							value = 'E';
						}
					}
					for (Chest c : listChests) {
						if (c.chestPosition.y == j && c.chestPosition.x == i && !c.isLooted) {
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

		//system("cls");

		std::cout << std::endl;
		std::cout << " ---------------------------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << " W A S D -> Movement" << std::endl;
		std::cout << " P -> Potion" << std::endl;
		std::cout << std::endl;

		char action;
		std::cout << " Enter your action: ";
		std::cin >> action;
	
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
			for (int i = 0; i < numEnemies; i++) {
				if (player.playerPosition.x == listEnemies[i].enemyPosition.x && player.playerPosition.y == listEnemies[i].enemyPosition.y) {
					Combat(&player, &listEnemies[i]);

					currentValue = 'E';
					break;					
				}
			}
			if (currentValue != 'E') {
				for (int i = 0; i < numChests; i++) {
					if (player.playerPosition.x == listChests[i].chestPosition.x && player.playerPosition.y == listChests[i].chestPosition.y) {
						OpenChest(&player, &listChests[i]);
						currentValue = 'C';
						break;
					}
				}
			}	

			//// Si coincide casilla entonces
			//if (currentValue == 'E') {
			//	Combat();
			//	currentValue == ' ';
			//}
			//else if (currentValue == 'C') {
			//	OpenChest();
			//}

		}
		else //If Player's Agility falls to 0, Enemies move again around the map
		{
			player.agility = player.maxAgility;
			EnemyMovement();
		}

		bool enemies = false;
		for (int i = 0; i < numEnemies; i++) {
			if (!listEnemies[i].isDead) {
				enemies = true;
				break;
			}
		}

		if (player.health <= 0 || !enemies) {
			GameOver(&player);
			gameOver = true;
		}

		
	}
	

}

void Map::EnemyMovement() {
	for (int i = 0; i < numEnemies; i++) {
		MapPosition auxPosition;
		bool valid;
		do {
			valid = true;
			auxPosition.x = GenerateClampedRandom(0, MAP_SIZE - 1);
			auxPosition.y = GenerateClampedRandom(0, MAP_SIZE - 1);
		
			valid = !CheckIfPositionsAreEqual(&auxPosition, &player.playerPosition);
			
			for (int j = 0; j < numChests && valid; j++) {
				valid = !CheckIfPositionsAreEqual(&auxPosition, &listChests[j].chestPosition);
			}

			for (int j = 0; j < numEnemies && valid; j++) {
				valid = !CheckIfPositionsAreEqual(&auxPosition, &listEnemies[j].enemyPosition);
			}
		} while (!valid);

		listEnemies[i].enemyPosition = auxPosition;
	}
}

void Map::GameOver(Player* p) {

	std::cout << std::endl;
	std::cout << " --------------- M I N I M A L   R P G ---------------" << std::endl;

	if (p->health <= 0) {
		std::cout << std::endl;
		std::cout << "              You Lost...Get good or something... :(" << std::endl;
	}
	else {
		std::cout << std::endl;
		std::cout << "              You Won! Good job! :D" << std::endl;
	}

	std::cout << std::endl;
	std::cout << "         We hope to see you again!!!" << std::endl;
	std::cout << std::endl;

	std::cout << " -----------------------------------------------------" << std::endl;

	system("pause");
}

void Map::OpenChest(Player* p, Chest* c) {
	system("cls");

	std::cout << "------ CHEST ------" << std::endl;
	std::cout << "\n > You open the chest and it contains: " << std::endl;
	std::cout << "\n\t> " << c->gold << " gold!" << std::endl;
	std::cout << "\t> Also you obtained " << c->gear.nameGear << std::endl;
	std::cout << "\t> - " << c->gear.descrptionGear << " -" << std::endl;
	std::cout << std::endl;

	if (c->ContainsPotion)
	{
		if (p->potion == p->maxPotion)
			std::cout << "\t\t> You already have max amount of potions!" << std::endl;
		else {
			std::cout << "\t> You got a potion!" << std::endl;
			p->potion++;
		}
	}

	std::cout << "\n______________________________________\n" << std::endl;
	c->isLooted = true;

	p->health +- c->gear.health;
	p->maxHealth += c->gear.health;
	p->health > p->maxHealth ? p->health = p->maxHealth : 0;


	p->maxStamina += c->gear.stamina;
	p->maxAgility += c->gear.agility;

	system("pause");
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

int Map::EnemyAction(Enemy* e) {

	// DEFEND
	if (e->health < e->maxHealth * 0.3f && e->stamina < e->maxStamina * 0.3f) {
		return 0;
	}

	// REST
	if (e->stamina < e->maxStamina * 0.2f) {
		return 1;
	}

	// ATTACK
	return 2;
}

void Map::Combat(Player* p, Enemy* e) {
	char action;
	int amountBet;

	while (!p->isDead && !e->isDead) {
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

		int eAction = EnemyAction(e);

		if (action == 'A' || action == 'a') {
			std::cout << "Enter the attack value " << "(Max " << player.maxStamina << "): ";
			std::cin >> amountBet;
			std::cout << std::endl;

			int eAttack;

			switch (eAction) {
			case 2:

				eAttack = GenerateClampedRandom(20, e->stamina);

				if (amountBet > eAttack) {
					e->health -= amountBet;
					e->stamina -= eAttack;
					player.stamina -= amountBet;
					if (p->stamina < 0) {
						p->stamina = 0;
					}
					if (e->stamina < 0) {
						e->stamina = 0;
					}
					std::cout << "You stroke the enemy with more guts and it received " << amountBet << " damage!" << std::endl;
				}
				else {
					p->health -= eAttack;
					p->stamina -= amountBet;
					e->stamina -= eAttack;
					if (player.stamina < 0) {
						player.stamina = 0;
					}
					if (e->stamina < 0) {
						e->stamina = 0;
					}
					std::cout << "The enemy was fearless of your offense and you took " << eAttack << " damage!" << std::endl;
				}
				break;
			case 0:
				e->health -= amountBet * 0.25f;
				e->stamina += e->maxStamina * 0.25f;
				p->stamina -= amountBet;
				if (p->stamina < 0) {
					p->stamina = 0;
				}
				if (e->stamina > e->maxStamina) {
					e->stamina = e->maxStamina;
				}
				std::cout << "The enemy defended itself, but anyway received " << amountBet * 0.25f << " damage\n" << std::endl;
				break;
			case 1:
				e->health -= amountBet;
				e->stamina = e->maxStamina;
				p->stamina -= amountBet;
				std::cout << "You savaged the defenseless enemy and dealt " << amountBet << " damage!\n" << std::endl;
				break;
			}
		}
		else if (action == 'D' || action == 'd') {

			int eAttack;

			switch (eAction) {
			case 2:

				eAttack = GenerateClampedRandom(20, e->stamina);

				p->health -= eAttack * 0.25f;
				e->stamina -= eAttack;
				if (e->stamina < 0) {
					e->stamina = 0;
				}
				std::cout << "You resisted most of the enemy's tackle, but received " << eAttack * 0.25f << " damage\n" << std::endl;
				break;
			case 0:
				e->stamina += e->maxStamina * 0.25f;
				if (e->stamina > e->maxStamina) {
					e->stamina = e->maxStamina;
				}
				std::cout << "You and the enemy look each other awkwardly while you both defend yourselves!\n" << std::endl;
				break;
			case 1:
				e->stamina = e->maxStamina;
				std::cout << "You defended yourself while the enemy took a breath!\n" << std::endl;
				break;
			}
			p->stamina += p->maxStamina * 0.25f;
			if (p->stamina > p->maxStamina) {
				p->stamina = p->maxStamina;
			}
		}
		else if (action == 'R' || action == 'r') {
			p->stamina = p->maxStamina;
			int eAttack;

			switch (eAction) {
			case 2:

				eAttack = GenerateClampedRandom(20, e->stamina);

				p->health -= eAttack;
				e->stamina -= eAttack;
				if (e->stamina < 0) {
					e->stamina = 0;
				}
				std::cout << "You blocked most of the enemy's hit, but received " << eAttack << " damage\n" << std::endl;
				break;
			case 0:
				e->stamina += e->maxStamina * 0.25f;
				if (e->stamina > e->maxStamina) {
					e->stamina = e->maxStamina;
				}
				std::cout << "The enemy lost it's chance and blocked an imaginary hit!\n" << std::endl;
				break;
			case 1:
				e->stamina = e->maxStamina;
				std::cout << "You and the enemy take a breath together, the battle end is near!\n" << std::endl;
				break;
			}

		}
		else if ((action == 'P' || action == 'p') && p->potion > 0) {

			int eAttack = eAttack = GenerateClampedRandom(20, e->stamina);

			if (p->potion <= 0) {
				std::cout << "You have no potions!" << std::endl;
			}
			else {
				std::cout << "You chose to live one more turn and healed, but the enemy hit you with " << eAttack << " damage!" << std::endl;
				p->health += p->maxHealth * 0.4f;
				p->potion--;
			}
		}

		p->health <= 0 ? p->isDead = true : false;
		e->health <= 0 ? e->isDead = true : false;

		system("pause");
		system("cls");
	}
}

