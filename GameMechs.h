#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <ctime>  // Changed to <ctime> for consistency
#include "objPos.h"

using namespace std;

class GameMechs
{
private:
    char input;       // Stores current player input
    bool exitFlag;    // Flag to indicate game exit
    bool loseFlag;    // Flag to indicate game loss
    int score;        // Player's score
    int boardSizeX;   // Board width
    int boardSizeY;   // Board height

public:
    GameMechs();                      // Default constructor
    GameMechs(int boardX, int boardY); // Specialized constructor
    /* No need for a destructor since no heap data members are used
    Therefore, we can just use the default destructor */

    bool getExitFlagStatus();          // Get exit flag status
    void setExitTrue();                // Set exit flag to true

    char getInput();                   // Get current input
    void setInput(char this_input);    // Set input
    void clearInput();                 // Clear input

    int getBoardSizeX();               // Get board width
    int getBoardSizeY();               // Get board height
};

#endif