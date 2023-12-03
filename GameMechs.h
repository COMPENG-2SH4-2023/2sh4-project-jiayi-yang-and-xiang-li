#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib> // Provides srand() and rand()
#include <time.h>  // Can be replaced by <ctime>
                   // Provides time()

#include "objPos.h"
#include "objPosArrayList.h"


using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        // Reference to the food's position list
        objPos foodPos;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();

        
        bool getExitFlagStatus();
        void setExitTrue();
//============================================================
        bool getLoseFlagStatus(); // Added to the header file
        void setLoseFlag(); // Added to the header file

        int getScore();
        void incrementScore();
//=====================================================
        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(objPosArrayList* blockOff); // You need to upgrade this to ArrayList type
        void getFoodPos(objPos &returnPos);
      

};

#endif