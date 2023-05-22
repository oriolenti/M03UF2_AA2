#include "Player.h"

void InitializePlayer(Player* player) {
    MapPosition playerPosition;
    playerPosition.x = 3;
    playerPosition.y = 2;
    player->playerPosition = playerPosition;

    player->agility = 3;
    player->health = 100;
    player->stamina = 100;
    player->gold = 0;
    player->potion = MAX_POTION;

    player->maxAgility = 3;
    player->maxHealth = 100;
    player->maxStamina = 100;

}