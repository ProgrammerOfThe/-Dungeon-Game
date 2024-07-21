#pragma once

#include <iostream>
#include <regex>

#define OBJECTS_NAME 10
#define OBJECTS_COORDINATES 10

std::string objectName[OBJECTS_NAME] = {"Hello", "someting"};
int objectXPos[OBJECTS_COORDINATES] = {2};  // Define object X positions as an array
int objectYPos[OBJECTS_COORDINATES] = {3};  // Define object Y positions as an array

#define OBJECT_COLLISION(playerXPos, playerYPos, objectCount) \
  for (int i = 0; i < objectCount; i++) { \
    if (playerXPos == objectXPos[i] && playerYPos == objectYPos[i]) { \
      std::cout << "You met " << objectName[i] << '\n'; \
    } \
  }

// object is like a desk or a lamp
// Enitity is like a character or a enemy sprite

enum OBJECT_TYPE{
  ARMOR = 1,
  WEAPON = 2,
  FOOD = 3
    
};

OBJECT_TYPE OBJECT_TYPE;

struct Object{
  // this just a template for any object to create
  std::string name;
  std::string description;
  
  bool consumable;
  int objectType; // equals one of the enums
  bool equiped;
  
};

struct Sword : Object{
  const std::string name = "Sword";
  const std::string description = "A sword";

  const bool consumable = false;
  bool equiped = false;
  
  const int objectType = WEAPON;
  
  void printAttribuites(){
    std::cout << "Name: "<< name << '\n';
    std::cout << "Description: " << description << '\n';

    if (consumable == true){
      std::cout << "Consumable: True\n";
    }else if (consumable == false){
      std::cout << "Consumable: False\n";
    }
    
    std::cout << "Type: " << objectType << '\n';
    
  }
  
};
