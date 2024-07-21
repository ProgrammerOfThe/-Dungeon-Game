#pragma once

enum DungeonStatus {
    NotCleared = false,
    Cleared = true,
};

struct Dungeon {
    int totalEnemies = 1;
    
    const int MAP_WIDTH = 5;
    const int MAP_HEIGHT = 5;
    
    int dungeonSize = MAP_WIDTH * MAP_HEIGHT;
    int dungeonRooms = 1;
   

};
