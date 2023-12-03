#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in ArrayList
        void updatePlayerDir();
        void movePlayer();
        char getPlayerDir(); // Declaration of a new function return the direction of the player
        bool checkFoodConsumption();
        void increasePlayerLength();
        bool checkSelfCollision(); 
        
    private:
        objPosArrayList* playerPosList;   // Upgrade this in iteration 3 to an ArrayList
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif