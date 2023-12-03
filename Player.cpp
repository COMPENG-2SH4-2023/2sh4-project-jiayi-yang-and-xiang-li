#include "Player.h"
#include "objPosArrayList.h"
#include "objPos.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    
}


Player::~Player()
{
    // Delete any heap members here
    // Do not need a square bracket here since this will call the ~objArrayList()
    delete playerPosList;

}

objPosArrayList* Player::getPlayerPos()
{   
    // Return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    //where do I get the input??? How do I check for inputs?
    //Hint 1. definitely not by calling MacUILib_getchar()!!!
    //     2. coordinate with your team member who's designing GameMechanism class
    //     3. there will be a method in GameMechanism class that collectively checks inoput and store the most recent input. you just need to figure out how to get to it.
    //        How?? it lies within the GameMechs* inside your private member


    char input = mainGameMechsRef -> getInput();

    // PPA3 input processing logic
    switch(input)
    {   
        // Shut down the program with the exit key "ESC"
        case 27:
            mainGameMechsRef -> setExitTrue();
            break;        

        case 'w':
            if(myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        
        case 'a':  
            if(myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
          
        case 's': 
            if(myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'd':  
            if(myDir != LEFT)
            {
                myDir = RIGHT;
            }
            
            break;

        default:
            break;

    }

}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // Holding the pos information of the current head
    objPos currentHead;

    playerPosList->getHeadElement(currentHead);


    switch(myDir)
    {
        case UP:
            currentHead.y--;
            if(currentHead.y <= 0)
            {
                currentHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case DOWN:
            currentHead.y++;
            if(currentHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            {
                currentHead.y = 1;
            }
            break;
        case LEFT:
            currentHead.x--;
            if(currentHead.x <= 0)
            {
                currentHead.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case RIGHT:
            currentHead.x++;
            if(currentHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            {
                currentHead.x = 1;
            }
            break;
        
        default:
            break;


    }

    // New current head should be inserted to the head of the list
    playerPosList->insertHead(currentHead);
    // Then, remove tail
    playerPosList->removeTail();

}

char Player::getPlayerDir()
{
    switch(myDir)
    {
        case UP:
            return 'U';

        case DOWN:
            return 'D';

        case LEFT:
            return 'L';

        case RIGHT:
            return 'R';

        default:
            return '\0';


    }
}

bool Player::checkFoodConsumption() {
    // Get the player's head position
    playerPosList = getPlayerPos();
    objPos headPos;
    playerPosList->getHeadElement(headPos);
    
    // Get the food position directly from the GameMechs class
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

    // Check if the head position matches the food position
    return headPos.isPosEqual(&foodPos);
}

void Player::increasePlayerLength() {
    // Get the current player position
    playerPosList = getPlayerPos();

    // Create a new head position based on the current head position
    objPos newHeadPos;
    playerPosList->getHeadElement(newHeadPos);

    // Add the new head position to the player's body
    playerPosList->insertHead(newHeadPos);
}

bool Player::checkSelfCollision() {
    // Get the player's head position
    playerPosList = getPlayerPos();
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    // Iterate through the player's position list to check for collisions with the head
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos bodyPart;
        playerPosList->getElement(bodyPart, i);
        
        if (i > 0 && headPos.isPosEqual(&bodyPart)) {
            // Collision detected with any body part except the head
            return true;
        }
    }
    
    // No collision detected
    return false;
}



