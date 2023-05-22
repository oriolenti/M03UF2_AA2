#include "map.h"

#include <vector>
#include <cstdlib>
#include <ctime>

int GenerateClampedRandom(int min, int max) {
	return (rand() % (max - min + 1)) + min; // rand() % (long_intervalo + 1 ) + min
}

// returns true if both position are located on the same spot
bool CheckIfPositionsAreEqual(MapPosition* position1, MapPosition* position2) {
	return position1->x == position2->x && position1->y == position2->y; // same as with if....
}