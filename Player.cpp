#include "Player.h"
#include "Food.h"
#include <stdio.h>

using namespace std;

// Constructor: initializes player position, references, and state
Player::Player(GameMechs* thisGMRef, Food* pFood)
{
    mainGameMechsRef = thisGMRef;  // Game mechanics reference
    foodRef = pFood;               // Food object reference
    score = 0;                     // Initialize score
    movement = STILL;              // Initial movement state

    playerPosList = new objPosArrayList();  // Create position list

    // Set initial player position at board center
    objPos temp(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(temp);

    srand(time(NULL));  // Seed random generator
}

// Destructor: cleanup dynamic memory
Player::~Player()
{
    delete[] playerPosList;  // Free position list memory
    playerPosList = nullptr;
}

// Returns reference to the player's position list
objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

// Updates player's movement direction based on input
void Player::updatePlayerDir()
{
    char BTNpressed = mainGameMechsRef->getInput();  // Get input

    switch (BTNpressed)
    {
        case 27:  // Escape key exits the game
            mainGameMechsRef->setExitTrue();
            break;
        case 'W': case 'w':  // Move up
            if (movement != DOWN || movement == STILL) movement = UP;
            break;
        case 'S': case 's':  // Move down
            if (movement != UP || movement == STILL) movement = DOWN;
            break;
        case 'A': case 'a':  // Move left
            if (movement != RIGHT || movement == STILL) movement = LEFT;
            break;
        case 'D': case 'd':  // Move right
            if (movement != LEFT || movement == STILL) movement = RIGHT;
            break;
        default:  // Ignore invalid inputs
            break;
    }
}

// Handles player movement and food collisions
void Player::movePlayer()
{
    objPos playerPos = playerPosList->getHeadElement();  // Get head position

    // Update position based on movement direction
    switch (movement)
    {
        case UP:    playerPos.pos->y--; break;
        case DOWN:  playerPos.pos->y++; break;
        case LEFT:  playerPos.pos->x--; break;
        case RIGHT: playerPos.pos->x++; break;
        case STILL: break;
    }

    // Wrap around if player reaches board edges
    if (playerPos.pos->x >= (mainGameMechsRef->getBoardSizeX() - 1)) playerPos.pos->x = 1;
    else if (playerPos.pos->x <= 0) playerPos.pos->x = mainGameMechsRef->getBoardSizeX() - 2;

    if (playerPos.pos->y >= (mainGameMechsRef->getBoardSizeY() - 1)) playerPos.pos->y = 1;
    else if (playerPos.pos->y <= 0) playerPos.pos->y = mainGameMechsRef->getBoardSizeY() - 2;

    playerPosList->insertHead(playerPos);  // Add new head position
    playerPosList->removeTail();           // Remove tail for movement effect

    // Check for food collisions
    objPosArrayList* foodPosList = foodRef->getFoodPos();

    for (int i = 0; i < foodPosList->getSize(); i++)
    {
        objPos foodPos = foodPosList->getElement(i);

        // Collision detected
        if (playerPos.pos->x == foodPos.pos->x && playerPos.pos->y == foodPos.pos->y)
        {
            int num_growth = (foodPos.getSymbol() == '3') ? 3 : 1;  // Special food effect
            if (foodPos.getSymbol() == '-')  // Shrink effect
            {
                num_growth = 0;
                if (playerPosList->getSize() > 1) playerPosList->removeTail();
            }

            // Grow player based on food type
            for (int w = 0; w < num_growth; w++)
            {
                switch (movement) {
                    case UP:    playerPos.pos->y--; break;
                    case DOWN:  playerPos.pos->y++; break;
                    case LEFT:  playerPos.pos->x--; break;
                    case RIGHT: playerPos.pos->x++; break;
                    case STILL: break;
            }

            // Wrap around logic
            if (playerPos.pos->x >= (mainGameMechsRef->getBoardSizeX() - 1)) playerPos.pos->x = 1;
            else if (playerPos.pos->x <= 0) playerPos.pos->x = (mainGameMechsRef->getBoardSizeX() - 2);
            if (playerPos.pos->y >= (mainGameMechsRef->getBoardSizeY() - 1)) playerPos.pos->y = 1;
            else if (playerPos.pos->y <= 0) playerPos.pos->y = (mainGameMechsRef->getBoardSizeY() - 2);
            playerPosList->insertHead(playerPos);
            }

            // Update score and regenerate food
            score += (foodPos.getSymbol() == '3') ? 6 : 1;
            foodRef->generateFood(playerPosList);
            break;
        }
    }
}

// Checks for self-collision
bool Player::checkSelfCollision()
{
    objPos playerHead = playerPosList->getHeadElement();

    // Compare head position with body positions
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos bodyPart = playerPosList->getElement(i);
        if (playerHead.pos->x == bodyPart.pos->x && playerHead.pos->y == bodyPart.pos->y) return true;
    }
    return false;
}

// Returns the player's current score
int Player::getScore()
{
    return score;
}
