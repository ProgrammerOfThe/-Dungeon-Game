#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <string.h>


// header files
#include "../Libs/player.hh"
#include "../Libs/enemy.h"
#include "../Libs/dungeon.h"
#include "../Libs/macro.h"
#include "../Libs/menu.hh"
#include "../Objects/objCreator.hpp"
 
 /* 
 * IMPLEMTIONS:
 * 
 * Recode the collison system so there isn't a delay and don't have to use 2 different collision for objects.
 * BUGS:
 *  
 * 
 * 
 * FIXED BUGS:
 *  Character stuck once battle is done; the break was put after the Battle so it wouldn't update the position;
 *  xPos not updating and yPos; It was in the wrong function when updated it was changed in the main loop not the function loop.
 *  Collision Needs fixing; Collision was fixed it was just how collision was made.
 * 
 * UPDATES:
 * 	V1(June 1st-V2(Whenever that comes out)):
 * 		Movement was added;
 * 		Collision was implemented and fixed;
 * 		Battle Component was made;
 *    	CCLEAN UP CODE; separated everything into different files.
 *	    Enemy entity needs to be made; Added E to the dungeon map and assigned an x and y coordinate to it.
 * 		Game menu
 *      Code a client that holds all the x and y of both the player and the enemy starting pos.
 * */
 
 
 
 
/// Define the size of the dungeon map
const size_t MAP_WIDTH = 10;
const size_t MAP_HEIGHT = 10;
const std::string filename = "playerXY.txt";

// Define the dungeon map as a 2D array
char dungeonMap[MAP_HEIGHT][MAP_WIDTH] = {
  {'*', '*', '*', '*', '*'},
  {'*', ' ', 'E', ' ', '*'},
  {'*', ' ', ' ', '@', '*'},
  {'*', ' ', ' ', ' ', '*'},
  {'*', ' ', ' ', ' ', '*'},
  {'*', '*', '*', '*', '*'}
};

struct Items{
	std::string npcChar = "@";   // npc
	std::string tableChar = "|"; // table
	// std::string wallChar = "*"; // wall already declared wall in movement and it already checks so this line is useless;
		
	struct selectedItems{
		char selectedObj = '@';
		
		size_t xPos = 3;
		size_t yPos = 2;
	};
	
	selectedItems selectedItem; // we can use a struct in a struct.
	void npcInteraction(){
		
		std::cout << "Npc: Hello \n";
	}
	
	void tableInteraction(){
		std::cout << "You interact with the table \n";
	}
	
};

struct Map : Items{
	selectedItems selectedItem;
	
	size_t x = selectedItem.xPos;
	int y = selectedItem.yPos;
	char selectedObj = selectedItem.selectedObj;
	
	void conversation(){
		// most likely make a npc class which deals with all the npc's.
	
	}
	
	// Just collision would do;
	
  bool objectCollision(Player *player) {
    if (player->xPos == selectedItem.xPos && player->yPos == selectedItem.yPos){
			return true;
		}
	
    return false;
 };	
};

// Function to print the dungeon map
void printMap() {
	
    for (size_t y = 0; y < MAP_HEIGHT; ++y) {
        for (size_t x = 0; x < MAP_WIDTH; ++x) {		
            std::cout << dungeonMap[y][x] << ' ';
        }
        std::cout << '\n';
    }
}


int movement() {
	Items items;
	// selectedItems selectedItem; is a subclass of Items which would mean we would have to declare the struct inside of items after we declare selectedItems,
	items.selectedItem.selectedObj = '#';
    char input;

    // Create objects and initialize variables
    Player* player = new Player;
    Enemy* enemy = new Enemy;
    Dungeon* dungeon = new Dungeon;
    Map* map = new Map;
    DungeonStatus dungeonStatus;
    // Initialize the player's position
    
    // Print the initial dungeon map
    printMap();

    // Game loop
    while (true) {
        std::cout << "Enter your move (w/a/s/d): ";
        std::cin >> input;

        // Handle movement based on user input
        switch (input) {
            case 'w': // Move up
              if (player->yPos > 0) {
                if (dungeonMap[player->yPos - 1][player->xPos] != '*') {
                  if (player->collision(enemy)) {
                    player->battle(enemy, dungeon, dungeonStatus);
                  }
                        
                	if (map->objectCollision(player)){
                		std::cout << "You collided with a object \n";
										// code the reaction with the player like if the selected object is the table then we run that or make a switch inside of the if statement with the objectCollision stuff.
										// we check what object we collided with and then do the apporiate interaction func
										switch(items.selectedItem.selectedObj){
											case '@':
												items.npcInteraction();
												break;
											case '|':
												items.tableInteraction();
												break;
											default:
												break;
										}
								}
								
              	dungeonMap[player->yPos][player->xPos] = ' ';
              	player->yPos--; // Subtract 1 from the y-axis position (move up)
              	dungeonMap[player->yPos][player->xPos] = 'P'; // Lets you know what character we are moving
              	player->saveXY(filename);
                
              	}else{
                	std::cout << "You hit a wall\n";
              	}
                
            	}else{
              	std::cout << "You cannot move up\n";
            	}
            break;
            
            case 'a': // Move left
              if (player->xPos > 0) {
                if (dungeonMap[player->yPos][player->xPos - 1] != '*') {
                  if (player->collision(enemy)) {
                    player->battle(enemy, dungeon, dungeonStatus);        
                  }
                        
            			if (map->objectCollision(player)){
										std::cout << "You collided with a object \n";
										// code the reaction with the player like if the selected object is the table then we run that or make a switch inside of the if statement with the objectCollision stuff.
									switch(items.selectedItem.selectedObj){
										case '@':
											items.npcInteraction();
											break;
										case '|':
											items.tableInteraction();
											break;
										default:
											break;
									}
								}
                
                map->objectCollision(player);
                dungeonMap[player->yPos][player->xPos] = ' ';
                player->xPos--; // Subtract 1 from the x-axis position (move left)
                dungeonMap[player->yPos][player->xPos] = 'P';
                player->saveXY(filename);
                }else{
                  std::cout << "You hit a wall\n";
                }
                
              }else{
                std::cout << "You cannot move left\n";
              }
              
              break;
            case 's': // Move down
              if (player->yPos < MAP_HEIGHT - 1) {
                if (dungeonMap[player->yPos + 1][player->xPos] != '*') {
                  if (player->collision(enemy)) {
                    player->battle(enemy, dungeon, dungeonStatus);         
                  }
                        
                if (map->objectCollision(player)){
									std::cout << "You collided with a object \n";
									// code the reaction with the player like if the selected object is the table then we run that or make a switch inside of the if statement with the objectCollision stuff.
								switch(items.selectedItem.selectedObj){
									case '@':
										items.npcInteraction();
										break;
									case '|':
										items.tableInteraction();
										break;
									default:
										break;
								}
							}
              map->objectCollision(player);
              dungeonMap[player->yPos][player->xPos] = ' ';
              player->yPos++; // Add 1 to the y-axis position (move down)
              dungeonMap[player->yPos][player->xPos] = 'P';
							player->saveXY(filename);
            
            }else{
              std::cout << "You hit a wall\n";
            }
            
          }else{
            std::cout << "You cannot move down\n";
          }
          
          break;
          
          case 'd': // Move right
            if (player->xPos < MAP_WIDTH - 1) {
              if (dungeonMap[player->yPos][player->xPos + 1] != '*') {
              	if (player->collision(enemy)) {
                  	player->battle(enemy, dungeon, dungeonStatus);         
                }
              	if (map->objectCollision(player)){
									std::cout << "You collided with a object \n";
									// code the reaction with the player like if the selected object is the table then we run that or make a switch inside of the if statement with the objectCollision stuff.
									switch(items.selectedItem.selectedObj){
									case '@':
										items.npcInteraction();
										break;
									case '|':
										items.tableInteraction();
										break;
									default:
										break;
								}
							}
              map->objectCollision(player);
              dungeonMap[player->yPos][player->xPos] = ' ';
              player->xPos++; // Add 1 to the x-axis position (move right)
              dungeonMap[player->yPos][player->xPos] = 'P';
              player->saveXY(filename);
              
              }else{
                std::cout << "You hit a wall\n";
              }
            }else{
              std::cout << "You cannot move right\n";
            }
            break;

            case 'i':
            	
            	break;
            	            
            default:
              std::cout << "Invalid input. Try again.\n";
              continue; // Continue to the next iteration of the loop
        	}

        	// Print the updated dungeon map
        	// system("clear");

        	std::cout << player->xPos << ' ' <<  player->yPos << '\n';
        	std::cout << enemy->xPos << ' ' << enemy->yPos << '\n';
        	printMap();
        
        
    		}

    	delete player;
    	delete enemy;
    	delete dungeon;
    	delete map;
    	
    	return 0;
}

int main() {
	menu();
  movement();
}
