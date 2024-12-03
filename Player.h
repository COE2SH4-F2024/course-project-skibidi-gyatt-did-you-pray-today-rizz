#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"



class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STILL};  // This is the direction state

        Player(GameMechs* thisGMRef, Food* pFood);
        ~Player();
        
        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();
        bool checkSelfCollision();
        int getScore();
    private:
        objPos playerPos;   // Upgrade this in iteration 3.
        objPosArrayList* playerPosList;       
        enum Dir movement;

        //Used for bonus
        int score;
        

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
        Food* foodRef;
};

#endif 
