#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"
#include "GameMechs.h"


class Food
{
    private:
        GameMechs* mainGameMechsRef;
        objPosArrayList* foodBucket;

    public:
        
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos();
};





#endif 
