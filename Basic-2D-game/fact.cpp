
#include "fact.h"
#include <cstdlib>
#include <iostream>

using namespace std;
namespace FactorySpace
{
    //method will be used to gen random numbers which will be
    //used to place the entities into the gameWorld
    int rangedRandom(int intMin, int intMax)
    {
        int intRange = intMax - intMin + 1;
        return rand() % intRange + intMin;
    }

    //the method checks if the moving entities are within the world
    bool isInWorld(GameWorld recWorld, int intRow, int intCol)
    {
        if(intRow < 0) return false;
        if(intRow >= recWorld.intRows) return false;
        if(intCol < 0) return false;
        if(intCol >= recWorld.intCols) return false;

        return true;
    }

    //method will be used to place entities randomly into the gameworld;
    void placeEntities(GameWorld recWorld, GameEntity eEntity, int intCount)
    {
        int intDR = rangedRandom(0, recWorld.intRows - 1);
        int intDC = rangedRandom(0, recWorld.intCols - 1);

        //will place the entities a certain number of times
        while(intCount > 0)
        {
            if(recWorld.aryWorld[intDR][intDC] == SPACE)
            {
                recWorld.aryWorld[intDR][intDC] = eEntity;
                intCount--;
            }
            intDR = rangedRandom(0, recWorld.intRows - 1);
            intDC = rangedRandom(0, recWorld.intCols - 1);
        }
    }

    //method will be used to desplay the world onto the standard output
    void _showWorld(GameWorld recWorld)
    {
        system("cls");
        for(int r = 0; r < recWorld.intRows; r++)
        {
            for(int c = 0; c < recWorld.intCols; c++)
            {
                if((r == recWorld.intPR) &&
                        (c == recWorld.intPC))
                {
                    cout << ARY_SYMBOLS[PLAYER] << ' ';
                } else
                {
                    cout << ARY_SYMBOLS[recWorld.aryWorld[r][c]] << ' ';
                }
            }
            cout << endl;
        }
    }

    //method will be used to move the player within the gameworld
    //the player will only move if the movement is within the world
    void _movePlayer(GameWorld& recWorld, Direction eDir)
    {
        int intDR = recWorld.intPR;
        int intDC = recWorld.intPC;

        switch(eDir)
        {
            case UP:
                intDR--;// move up
                break;
            case NE: //move north east
                intDR--;
                intDC++;
                break;

            case DOWN://move down
                intDR++;
                break;

                case SE://move south east
                intDR++;
                intDC++;
                break;

            case LEFT://move left
                intDC--;
                break;

                case SW://move south west
                intDR++;
                intDC--;
                break;

            case RIGHT://move right
                intDC++;
                break;

                case NW://move north west
                intDR--;
                intDC--;
                break;
        }
        //checking if the chosen movement is withi the world
        if(isInWorld(recWorld, intDR, intDC))
        {
            static int check = 0;//keeps track of the collected parts
            static int lives = 10;//keeps track of the number of lives
            static int eaten = 0;//keeps track of the amount of parts collected
            int intEntity = recWorld.aryWorld[intDR][intDC];
            //player will only be able to collect parts only if they have no parts in posesion
            if ((intEntity == PARTS) && check == 0)
            {
                recWorld.intPR = intDR;
                recWorld.intPC = intDC;
            }
            if(intEntity == SPACE || intEntity == FACTORY)
            {
                //checking if the player is allowed to deliver parts to the factory
                if (intEntity == FACTORY && check == 1)
                {
                    check = 0;
                    eaten++;
                    lives += 10;
                }
                //checking is the player is allowed to make a visit to the factory
                //if not then the player will lose 10 points
                else if (intEntity == FACTORY && check == 0){
                    lives -=10;
                }
                recWorld.intPR = intDR;
                recWorld.intPC = intDC;
            }
            //allowing the player to collect the part
            if(intEntity == PARTS)
                check = 1;
            //setting the location of the collected part to nothing (a space)
            if(check == 1 && recWorld.aryWorld[recWorld.intPR][recWorld.intPC] == PARTS)
                recWorld.aryWorld[intDR][intDC] = SPACE;
            //weird math that checks if the player has collected all parts
            if (eaten == ((recWorld.intRows*recWorld.intCols*5)/100)){
                cout << "YOU WIN!!" << endl;
                exit(SUCCESS);
            }
            //game will end if the player gets zero lives
            if (lives == 0){
                cout << "YOU LOSE !!" << endl;
                exit(game_lost);
            }
            recWorld.remaining = eaten;
            recWorld.points = lives;
        }
    }

    //method that will be used to deallocate memory
    void _freeWorld(GameWorld& recWorld)
    {
        for(int r = 0; r < recWorld.intRows; r++)
            delete [] recWorld.aryWorld[r];
        delete [] recWorld.aryWorld;
        recWorld.aryWorld = nullptr;
    }

    //method being used to create the world
    GameWorld makeWorld(int intRows, int intCols)
    {
        GameWorld recWorld;
        recWorld.intRows = intRows;
        recWorld.intCols = intCols;

        recWorld.aryWorld = new GameRow[recWorld.intRows];//allocaating memory of total rows size
        for(int r = 0; r < recWorld.intRows; r++)
        {
            recWorld.aryWorld[r] = new int[recWorld.intCols];//for each rows allocate columns
            for(int c = 0; c < recWorld.intCols; c++)
                recWorld.aryWorld[r][c] = SPACE;//setting all the indexis to space ('.')
        }

        placeEntities(recWorld, FACTORY, 1);//placing a factory randomly within the world
        placeEntities(recWorld, PARTS, (recWorld.intRows*recWorld.intCols*5)/100);//weird math will add 5% of parts within the world

        recWorld.intPR = rangedRandom(0, recWorld.intRows - 1);
        recWorld.intPC = rangedRandom(0, recWorld.intCols - 1);
        //placing the parts randomly within the game given the locaation is free (space '.')
        bool blnPlaced = false;
        while(!blnPlaced)
        {
            if((recWorld.aryWorld[recWorld.intPR][recWorld.intPC] == SPACE) ||
                    (recWorld.aryWorld[recWorld.intPR][recWorld.intPC] == PARTS))
            {
                blnPlaced = true;
            }
            //more random numbers for more parts
            recWorld.intPR = rangedRandom(0, recWorld.intRows - 1);
            recWorld.intPC = rangedRandom(0, recWorld.intCols - 1);
        }
        //pointers to functions being assigned the address to those functions
        recWorld.showWorld = &_showWorld;
        recWorld.movePlayer = &_movePlayer;
        recWorld.freeWorld = &_freeWorld;
        return recWorld;
    }
}
