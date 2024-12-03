#include "MacUILib.h"
#include "Player.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

Food::Food(GameMechs* thisGMRef)
{
    // Initialize game mechanics reference
    mainGameMechsRef = thisGMRef;

    // Create and initialize food object list
    foodBucket = new objPosArrayList();

    // Add initial generic food objects to the list
    objPos temp(0, 0, 's');
    foodBucket->insertHead(temp);  // Insert initial food
    foodBucket->insertTail(temp);  // Add more food
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
}

Food::~Food()
{
    // Delete food object list
    delete[] foodBucket;
    foodBucket = nullptr;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int alreadyChosen, candidateX, candidateY;

    objPos foodPos, playerPos, otherFoodPos;

    // Generate 5 distinct food objects
    for (int z = 0; z < 5; z++)
    {
        alreadyChosen = 1;
        while (alreadyChosen)
        {
            alreadyChosen = 0;

            // Generate random x and y within valid range
            candidateX = (rand() % (mainGameMechsRef->getBoardSizeX() - 3)) + 1;
            candidateY = (rand() % (mainGameMechsRef->getBoardSizeY() - 3)) + 1;

            // Check if position is taken by player or blocked area
            for (int i = 0; i < blockOff->getSize(); i++)
            {
                playerPos = blockOff->getElement(i);
                if ((candidateX == playerPos.pos->x) && (candidateY == playerPos.pos->y))
                {
                    alreadyChosen = 1;  // Keep generating
                    break;
                }
            }

            // Check if position is already taken by other food
            for (int j = 0; j < foodBucket->getSize(); j++)
            {
                otherFoodPos = foodBucket->getElement(j);
                if ((otherFoodPos.pos->x == candidateX) && (otherFoodPos.pos->y == candidateY))
                {
                    alreadyChosen = 1;  // Keep generating
                    break;
                }
            }

            // If position is valid, insert food
            if(!alreadyChosen)
            {
                foodPos.pos->x = candidateX;
                foodPos.pos->y = candidateY;
                if (z == 1) {
                    foodPos.symbol = '3';
                }
                else if (z == 3) {
                    foodPos.symbol = '-';
                }
                else {
                    foodPos.symbol = '$';
                }
                foodBucket->insertTail(foodPos);
                foodBucket->removeHead();
            }
        }
    }
}

objPosArrayList* Food::getFoodPos()
{
    // Return food object list
    return foodBucket;
}
