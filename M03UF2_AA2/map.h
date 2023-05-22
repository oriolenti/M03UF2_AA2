#pragma once

#define MAP_SIZE 5

struct MapPosition
{
	int x;
	int y;
};

int GenerateClampedRandom(int min, int max);
bool CheckIfPositionsAreEqual(MapPosition* position1, MapPosition* position2);