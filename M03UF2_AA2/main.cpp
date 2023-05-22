#include <iostream>
#include <ctime>
#include "MainManager.h"

int main() {
    srand(time(NULL));
    Map map;
    InitGame(&map);
    map.Dungeon();

    return 0;
}