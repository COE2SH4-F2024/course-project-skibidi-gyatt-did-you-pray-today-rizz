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
    objPos temp = {0,0,'s'};
    foodBucket->insertHead(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
    foodBucket->insertTail(temp);
}

Food::~Food()
{
    // Delete food object list
    delete[] foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    int alreadyChosen, candidateX, candidateY;
    
    objPos playerPos, foodPos, otherFoodPos;

    // Generate 5 distinct food objects
    for(int z = 0; z < 5; z++){
        
        alreadyChosen = 1;
        while(alreadyChosen)
        {
            alreadyChosen = 0;

            // Generate random x and y within valid range
            candidateX = (rand() % (mainGameMechsRef->getBoardSizeX() - 3)) + 1; 
            candidateY = (rand() % (mainGameMechsRef->getBoardSizeY() - 3)) + 1;

            // Check if position is taken by player
            for (int i = 0; i < blockOff->getSize(); i++){
                blockOff->getElement(playerPos, i);
                if((candidateX == playerPos.x) && (candidateY == playerPos.y))
                {
                    alreadyChosen = 1;  // Keep generating
                    break;
                }
            }

            // Check if position is already taken by other food
            for (int j = 0; j < z; j++) {
                foodBucket->getElement(otherFoodPos, j);
                if ((otherFoodPos.x == candidateX) && (otherFoodPos.y == candidateY)){
                    alreadyChosen = 1;  // Keep generating
                    break;
                }
            }

            // If position is valid, insert food
            if(!alreadyChosen)
            {
                foodPos.x = candidateX;
                foodPos.y = candidateY;
                if (z == 1) {
                    foodPos.symbol = '2';
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