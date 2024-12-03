#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"

class Food
{
    private:
        GameMechs* mainGameMechsRef;  // Reference to game mechanics
        objPosArrayList* foodBucket;  // List of food objects

    public:
        Food(GameMechs* thisGMRef);    // Constructor
        ~Food();                       // Destructor

        void generateFood(objPosArrayList* blockOff);  // Generate new food positions
        objPosArrayList* getFoodPos();                 // Get current food positions
};

#endif