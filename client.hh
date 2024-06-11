#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <unistd.h>

struct PlayerPosition {
    size_t x;
    size_t y;
};

PlayerPosition readPlayerPositionFromFile(const std::string& filename) {
    PlayerPosition playerPos;
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> playerPos.x >> playerPos.y;
        file.close();
    }
    
    return playerPos;
}

void clientWindow() {
    std::string filename = "playerXY.txt";
    PlayerPosition prevPlayerPos = {0, 0};

    while (true) {
        PlayerPosition currPlayerPos = readPlayerPositionFromFile(filename);

        if (currPlayerPos.x != prevPlayerPos.x || currPlayerPos.y != prevPlayerPos.y) {
            std::cout << "Player position: (" << currPlayerPos.x << ", " << currPlayerPos.y << ")\n";
            prevPlayerPos = currPlayerPos;
        }

        // Add any additional processing or actions required by the client

        // Sleep for a short interval to avoid excessive file reads
        sleep(2);
    }
}

#endif
