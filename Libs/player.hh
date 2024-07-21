/*
 * player.hh
 * 
 * Copyright 2024 Neo Zrync <yosefysrayl01@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#pragma once

#include <iostream>
#include <unistd.h>
#include <fstream>

#include "enemy.h"
#include "dungeon.h"
// Define the player structure
struct Player {
    size_t health = 15;
    size_t damage = 5;
    size_t xPos = 2;
    size_t yPos = 2;
    std::string input;
    std::string movementModifer = "2";



  bool collision(Enemy *enemy){
    // we check if the player collides with the boundaries of the dungeonSize and enemies
    if (xPos == enemy->xPos && yPos == enemy->yPos){
      std::cout << "You encountered an enemy at " << enemy->xPos << ' ' << enemy->yPos << '\n';

      return true;
    }
    return false;
  }

  void battle(Enemy* enemy, Dungeon* dungeon, DungeonStatus dungeonStatus) {
    if (dungeon->totalEnemies > 0) {
        std::cout << "Battle Begins!\n";
        sleep(3);
        system("clear");

        while (enemy->health > 0 && health > 0) {
            std::cout << "Player Turn: Attacking Monster\n";
            enemy->health -= damage;
            std::cout << "Enemy Health: " << enemy->health << '\n';

            if (enemy->health > 0) {
                // Enemy's turn to attack
                std::cout << "Enemy Turn: Attacking Player\n";
                health -= enemy->damage;
                std::cout << "Player Health: " << health << '\n';
            } else {
                std::cout << "Player won \n";
                dungeon->totalEnemies -= 1;

                if (dungeon->totalEnemies == 0) {
                    dungeonStatus = Cleared;
                    system("clear");
                    std::cout << "You cleared the dungeon \n";
                    break; // Exit the battle loop if all enemies are defeated
                } else {
                    std::cout << "There are still enemies remaining in the dungeon. \n";
                    break; // Exit the battle loop while continuing the game loop
                }
            }
        }
    } else if (dungeon->totalEnemies <= 0) {
        std::cout << "You found the carcass of a slain enemy\n";

        }
    }

    void saveXY(std::string filename){
		std::ofstream file(filename);
		file << xPos << '\n';
		file << yPos << '\n';
		file.close();
  }
};

