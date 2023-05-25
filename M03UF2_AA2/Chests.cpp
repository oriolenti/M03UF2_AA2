#include "Chests.h"


void InitializeChest(Chest* chest, MapPosition* chestPosition) {
     
    chest->isLooted = false;

    //-----POSITION
    chest->chestPosition = *chestPosition;

    //-----GOLD
    chest->gold = GenerateClampedRandom(50, 200);

    //-----POTION
    if (GenerateClampedRandom(1, 4) == 4) {
        chest->ContainsPotion = true;
    }
    else {
        chest->ContainsPotion = false;
    }

    //-----GEAR
    // TODO set the array of allGear at start of game
    chest->gear = gear[GenerateClampedRandom(0, 9)];
}