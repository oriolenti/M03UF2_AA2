
# include "Enemy.h"

void InitializeEnemy(Enemy* e, MapPosition* enemyPosition) {
    e->enemyPosition = *enemyPosition;

    e->isDead = false;

    e->health = GenerateClampedRandom(60,90);
    e->maxHealth = e->health;

    e->stamina = GenerateClampedRandom(60, 90);
    e->maxStamina = e->stamina;
}