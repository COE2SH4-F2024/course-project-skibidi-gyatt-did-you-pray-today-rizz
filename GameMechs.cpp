#include "GameMechs.h"
#include "MacUILib.h"
#include "Player.h"

// Default constructor: initializes default values for game mechanics
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    objPos food; // Placeholder for food position
}

// Specialized constructor: allows custom board size initialization
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
    objPos food; // Placeholder for food position
}

// Returns the current status of the exit flag
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

// Captures and returns the current player input if available
char GameMechs::getInput()
{
    if (MacUILib_hasChar() == 1) {
        input = MacUILib_getChar();
    }
    return input;
}

// Returns the board's width
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

// Returns the board's height
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

// Sets the exit flag to true, indicating the game should terminate
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Updates the stored input with the provided character
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// Clears the stored input, resetting it to 0
void GameMechs::clearInput()
{
    input = 0;
}
