#include "Chests.h"

void InitGears(Gear allGears[10]) {

}


void InitializeChest(Chest* chest, Gear allGears[10], MapPosition* chestPosition) {
    chest->gold = GenerateClampedRandom(50, 200);
    chest->isLooted = false;

    if (GenerateClampedRandom(1, 4) == 4) {
        chest->ContainsPotion = true;
    }
    else {
        chest->ContainsPotion = false;
    }
    // TODO set the array of allGear at start of game
    chest->gear = allGears[GenerateClampedRandom(0, 9)];

    chest->chestPosition = *chestPosition;
}