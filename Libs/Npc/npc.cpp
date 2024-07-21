#include <iostream>
#include <unistd.h>

int npcQuest(){
	std::cout << "Hello there, dear warrior. I am in need for help \n";
	sleep(1);
	std::cout << "You see the enemy over there, I need you to go kill him and then you will progress to the next level \n";
	
	return 0;
}

std::string questCompletion(){
	std::cout << "Thank you for clearing the dungeon you have leveled up to the next map. \n";
	
}