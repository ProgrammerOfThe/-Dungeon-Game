#pragma once

#include <iostream>
#include <unistd.h>

#define LENGTH 20
#define HEIGHT 20
#define SELF_TERMINATION 2
/*

###############
	Play
	Quit
###############
*/

bool menu(){
	std::string input;
	for(int i = 0; i < LENGTH; i++){
		std::cout << "#";
	}
	
	std::cout << "\n";
	
	std::cout << "	Play	\n";
	std::cout << "	Quit	\n";
	for(int j = 0; j < HEIGHT; j++){
		std::cout << "#";
	}
	std::cout << '\n';
	std::cout << ">> ";
	std::cin >> input;
	
	if (input == "Play"){
		// we just continue
		system("clear");
	}else{
		exit(SELF_TERMINATION);
	}
	
	return false;
}

