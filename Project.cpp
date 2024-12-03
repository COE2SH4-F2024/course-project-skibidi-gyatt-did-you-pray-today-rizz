#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//Global Pointer Declarations
GameMechs* pGame_Mechs = NULL;
Player* pPlayer = NULL;
Food* pFood = NULL;


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(pGame_Mechs->getExitFlagStatus() == false)  
    {
        GetInput(); 
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    
    //Game Mechanics Creation
    pGame_Mechs = new GameMechs(30, 15);

    //Food Creation
    pFood = new Food(pGame_Mechs);

    //Player Creation
    pPlayer = new Player(pGame_Mechs, pFood);
    objPosArrayList* snakeList;
    snakeList = (pPlayer->getPlayerPos());
    

    //Food Generation
    pFood->generateFood(snakeList);
   
}


void GetInput(void)
{
   //Part of GameMechs
}

void RunLogic(void)
{

    //Movement
    pPlayer->updatePlayerDir();
    pGame_Mechs->clearInput();//Nulls current input - No double processing
    pPlayer->movePlayer();


    //Check for player collision
    if(pPlayer->checkSelfCollision()){
    pGame_Mechs->setExitTrue();
    }
   
    
}

void DrawScreen(void)
{
    //Player Body List
    objPosArrayList* snakeList;
    snakeList = (pPlayer->getPlayerPos());

    //Food Piece List
    objPosArrayList* foodList;
    foodList = (pFood->getFoodPos());

    //Temp Player and Food positions
    objPos foodPos;
    objPos bodyPos;
    
    bool piece_placed = false;

   
    MacUILib_clearScreen();
        for (int i = 0; i < pGame_Mechs->getBoardSizeY(); i++) {//Y-axis
            for (int j = 0; j < pGame_Mechs->getBoardSizeX(); j++) {//X-axis

                piece_placed = false;
                
                //Border display
                if ((i == 0) || (i == pGame_Mechs->getBoardSizeY() - 1)) {
                    MacUILib_printf("#");
                }
                else if ((j == 0) || (j == pGame_Mechs->getBoardSizeX() - 1)){
                    MacUILib_printf("#");
                }

                //Special character
                else {

                    //Iterate through player list
                    for (int l = 0; l < (*snakeList).getSize(); l++){
                        bodyPos = snakeList->getElement(l); 
                        if (i == bodyPos.pos->y && j == bodyPos.pos->x) {
                            MacUILib_printf("%c", bodyPos.symbol);

                            piece_placed = true;//Don't place space and don't check food
                            break;
                        }
                    }

                    if (piece_placed == false) {//If a player character hasn't been placed
                    
                    //Iterate through food list
                    for (int l = 0; l < 5; l++){
                        foodPos = foodList->getElement(l);
                        if (i == foodPos.pos->y && j == foodPos.pos->x) {
                            MacUILib_printf("%c", foodPos.symbol);

                            piece_placed = true;//Don't place space
                            break;
                        }
                    }
                    }

                    if (piece_placed == false) {//Add space
                        MacUILib_printf(" ");
                    }
                    
                }

                }
            
        
            cout << endl;
    
    }

    //Game info
    cout << "Score: " << (pPlayer->getScore()) << endl; 
    cout << endl << "Controls: WASD (W, up; A, left; S, down;D, right)" << endl;
    cout << "Food Guide:" << endl << "$ -> Score + 1, Body Length + 1" << endl << "3 -> Score + 6, Body Length + 3" << endl << "- -> Score + 1, Body Length - 1 " << endl;
    cout << "Press [esc] to exit. Try not to run into yourself!" << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    
    MacUILib_clearScreen(); 

    //Ending messages
    if(pPlayer->checkSelfCollision()){//Player died
        cout << "Game Over:(" << endl;
        cout << "Final score: " << pPlayer->getScore() << endl;

        //Acheivement messsages
        if(pPlayer->getScore() <= 10) {
        cout << "Practice makes Perfect. You haven't practiced yet tho " << endl;
        }
        else if(pPlayer->getScore() <= 50) {
            cout << "Look at you go!" << endl;
        }
        else{
            cout << "GOAT tier!" << endl;
        }

    }
    else {//Player hit escape key
        cout << "Game ending..." << endl;
        cout << "Final score: " << pPlayer->getScore() << endl;
        cout << "Thanks for playing!" << endl;
    }
    
    
    MacUILib_uninit();

    //Free all variables on heap
    delete[] pPlayer;
    delete[] pGame_Mechs; 
    delete[] pFood;
}
