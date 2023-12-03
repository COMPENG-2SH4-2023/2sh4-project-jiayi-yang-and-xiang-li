#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"


using namespace std;

#define DELAY_CONST 100000

// OOD Benefit - very limited global var declaration
// In advanced OOD, you dont even need global variable
GameMechs* myGM;
Player* myPlayer;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }
    CleanUp();
    

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Make the board size 26x13
    myGM = new GameMechs(26, 13); 
    myPlayer = new Player(myGM);

    //think about when to generate the new food
    //think about whether you want to set up a debug key to call the food generation routine for verification
    //remember generateFood() requires player reference. You will need to provide it AFTER palyer object is instantiated
    

}

void GetInput(void)
{
    myGM->getInput();

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    
    if (!myPlayer->checkSelfCollision()) {
        objPosArrayList* playerPosList = myPlayer->getPlayerPos();

        // Check if the player collects the food
        if (myPlayer->checkFoodConsumption()) {
            // Increment player length
            myPlayer->increasePlayerLength();
            
            // Increment Score
            myGM->incrementScore();

            // Generate new food on the game board
            myGM->generateFood(playerPosList);
        }

        myGM->clearInput();
    } else {
        // Collision detected, set lose and exit flags
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }
}


void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    bool drawn;

    // Get the player pos
    objPosArrayList* playerPosList = myPlayer->getPlayerPos();
    objPos tempBody;

    // Get the food pos
    objPos foodPos;
    myGM->getFoodPos(foodPos); 
    

    // Draw border, player object and food object
    for (int i = 0; i < (myGM->getBoardSizeY()); i++) 
    {
        for (int j = 0; j < (myGM->getBoardSizeX()); j++) 
        {   
            drawn = false;

            // Player's position
            // Iterate through every elements in the list
            for(int k = 0; k < playerPosList->getSize(); k++)
            {
                playerPosList->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }
            // If player body was drawn, don't draw anything below
            if(drawn)
            {
                continue;
            }
            // Border
            if(i == 0 || i == (myGM->getBoardSizeY() - 1) || j == 0 || j == (myGM->getBoardSizeX() - 1)) 
            {
                MacUILib_printf("#");
            } 
            // Food position
            else if(i == foodPos.y && j == foodPos.x) 
            {
                MacUILib_printf("%c", foodPos.symbol);
            }
            // For empty space
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    
    }   

    // Debug Message
    MacUILib_printf("Score: %d\n", myGM->getScore()); 
    MacUILib_printf("======== DEBUG MESSAGE ========\n");
    // Print board size
    MacUILib_printf("Board Size: %d X %d\n", myGM->getBoardSizeX(), myGM->getBoardSizeY());
    // Print the player's direction
    MacUILib_printf("Player Direction: %c\n", myPlayer->getPlayerDir());
    // Print player's positions
    MacUILib_printf("Player Position: \n");
    for(int l = 0; l < playerPosList->getSize(); l++)
    {
        playerPosList->getElement(tempBody, l);
        MacUILib_printf("<%d, %d> ", tempBody.x, tempBody.y);

    }
    // Print the food's position
    MacUILib_printf("\nFood Position: <%d, %d>\n", foodPos.x, foodPos.y);


}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay

}


void CleanUp(void)
{
    MacUILib_clearScreen();  
  
    // If ending, you need to differentiate the end game state
    // LOST - display LOST message
    // otherwise, display ENDGAME message only
    if (myGM -> getExitFlagStatus() == 1 && myGM -> getLoseFlagStatus() == 1)
    {   // LOST message
        MacUILib_printf("YOU LOST! Your Score: %d", myGM->getScore());
    }
    else
    {   // ENDGAME message
        MacUILib_printf("GAME ENDED! Your Score: %d", myGM->getScore());
    }
    
    MacUILib_uninit();

    // Remove heap instances
    delete myGM;
    delete myPlayer;
}
