#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>
#include "objPos.h"


#include <cstdlib> // Provides srand() and rand()
#include <time.h>  // Can be replaced by <ctime>
                   // Provides time()

// Thinking about where to seed the RNG

GameMechs::GameMechs()
{
    input = 0;
    score = 0; // Score should start at 0    
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 20; // Default board size
    boardSizeY = 10;

    foodPos.setObjPos(-10, -10, 'o'); // Initialize foodpos outside of the game board(so to not be displayed)
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;  
    exitFlag = false;
    loseFlag = false;    
    boardSizeX = boardX; // Preferred board size
    boardSizeY = boardY;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate random x and y coord and make sure they are not on the border
    int x, y;

    do
    {
        x = 1 + rand() % (boardSizeX - 2);
        y = 1 + rand() % (boardSizeY - 2);
    } while (x == foodPos.x && y == foodPos.y);
    
    foodPos.setObjPos(x, y, 'o'); 
    
}

// Do you need a destructor?
GameMechs::~GameMechs()  
{
    // Perform any necessary cleanup here
}


bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

// Added to the source file
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = 1;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++; 

}
//==================

char GameMechs::getInput()
{
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = 1;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}


void GameMechs::generateFood(objPosArrayList* blockOff) {
    int x, y;

    // Generate random x and y coordinates for the food
    do {
        x = 1 + rand() % (boardSizeX - 2);
        y = 1 + rand() % (boardSizeY - 2);

        // Check whether the snake body overlaps with the position of food
        bool overlap = false;
        for (int i = 0; i < blockOff->getSize(); i++) {
            objPos tempPos;
            blockOff->getElement(tempPos, i);
            // Iterate through every single objPos element
            if (tempPos.x == x && tempPos.y == y) {
                overlap = true;
                break;
            }
        }

        if (!overlap) {
            break;  // Exit the loop if the food position is not on the snake's body
        }
    } while (true);

    foodPos.setObjPos(x, y, 'o');
}




void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}

