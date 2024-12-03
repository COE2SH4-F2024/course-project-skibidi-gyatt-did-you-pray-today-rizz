#include "Player.h"
#include "Food.h"
#include <stdio.h>

using namespace std;

// Constructor: initializes player position, references, and state
Player::Player(GameMechs* thisGMRef, Food* pFood)
{
    mainGameMechsRef = thisGMRef; // Game mechanics reference
    foodRef = pFood; // Food object reference
    score = 0; // Initialize score
    movement = STILL; // Initial movement state

    playerPosList = new objPosArrayList(); // Create position list

    // Set initial player position at board center
    objPos temp;
    temp.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(temp);

    srand(time(NULL)); // Seed random generator
}

// Destructor: cleanup dynamic memory
Player::~Player()
{
    delete[] playerPosList; // Free position list memory
}

// Returns reference to the player's position list
objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
}

// Updates player's movement direction based on input
void Player::updatePlayerDir()
{
    char BTNpressed = mainGameMechsRef->getInput(); // Get input

    switch (BTNpressed)
    {
        case 27: // Escape key exits the game
            mainGameMechsRef->setExitTrue();
            break;
        case 'W': case 'w': // Move up
            if (movement != DOWN || movement == STILL) movement = UP;
            break;
        case 'S': case 's': // Move down
            if (movement != UP || movement == STILL) movement = DOWN;
            break;
        case 'A': case 'a': // Move left
            if (movement != RIGHT || movement == STILL) movement = LEFT;
            break;
        case 'D': case 'd': // Move right
            if (movement != LEFT || movement == STILL) movement = RIGHT;
            break;
        default: // Ignore invalid inputs
            break;
    }
}

// Handles player movement and food collisions
void Player::movePlayer()
{
    objPos playerPos;
    playerPosList->getHeadElement(playerPos); // Get head position

    // Update position based on movement direction
    switch (movement)
    {
        case UP: playerPos.y--; break;
        case DOWN: playerPos.y++; break;
        case LEFT: playerPos.x--; break;
        case RIGHT: playerPos.x++; break;
        case STILL: break;
    }

    // Wrap around if player reaches board edges
    if (playerPos.x >= (mainGameMechsRef->getBoardSizeX() - 1)) playerPos.x = 1;
    else if (playerPos.x <= 0) playerPos.x = (mainGameMechsRef->getBoardSizeX() - 2);
    if (playerPos.y >= (mainGameMechsRef->getBoardSizeY() - 1)) playerPos.y = 1;
    else if (playerPos.y <= 0) playerPos.y = (mainGameMechsRef->getBoardSizeY() - 2);

    playerPosList->insertHead(playerPos); // Add new head position
    playerPosList->removeTail(); // Remove tail for movement effect

    // Check for food collisions
    objPosArrayList* foodPosL = foodRef->getFoodPos();
    objPos foodPos;

    for (int i = 0; i < 5; i++) {
        foodPosL->getElement(foodPos, i);

        // Collision detected
        if (playerPos.x == foodPos.x && playerPos.y == foodPos.y) {
            int num_growth = (foodPos.symbol == '3') ? 3 : 1; // Special food effect
            if (foodPos.symbol == '-') { // Shrink effect
                num_growth = 0;
                if (playerPosList->getSize() > 1) playerPosList->removeTail();
            }

            // Grow player based on food type
            for (int w = 0; w < num_growth; w++) {
                switch (movement) {
                    case UP: playerPos.y--; break;
                    case DOWN: playerPos.y++; break;
                    case LEFT: playerPos.x--; break;
                    case RIGHT: playerPos.x++; break;
                    case STILL: break;
                }

                // Wrap around logic
                if (playerPos.x >= (mainGameMechsRef->getBoardSizeX() - 1)) playerPos.x = 1;
                else if (playerPos.x <= 0) playerPos.x = (mainGameMechsRef->getBoardSizeX() - 2);
                if (playerPos.y >= (mainGameMechsRef->getBoardSizeY() - 1)) playerPos.y = 1;
                else if (playerPos.y <= 0) playerPos.y = (mainGameMechsRef->getBoardSizeY() - 2);

                playerPosList->insertHead(playerPos);
            }

            // Update score and regenerate food
            score += (foodPos.symbol == '3') ? 6 : 1;
            foodRef->generateFood(playerPosList);
            break;
        }
    }
}

// Checks for self-collision
bool Player::checkSelfCollision()
{
    objPos playerHead;
    playerPosList->getHeadElement(playerHead);

    // Compare head position with body positions
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos bodyPart;
        playerPosList->getElement(bodyPart, i);
        if (playerHead.x == bodyPart.x && playerHead.y == bodyPart.y) return true;
    }
    return false;
}

// Returns the player's current score
int Player::getScore()
{
    return score;
}
