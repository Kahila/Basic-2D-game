
#ifndef FACT_H
#define FACT_H

namespace FactorySpace
{
    //represent game entities
    enum GameEntity
    {
        SPACE,
        FACTORY,
        PARTS,
        PLAYER
    };
    const char ARY_SYMBOLS[] = {'.', 'F', '$', '@'};

    typedef int** GameArray;
    typedef int* GameRow;

    //represent the movements
    enum Direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NE,
        SE,
        SW,
        NW
    };
    //represent the reeturn or exit code
    enum StatusCode
    {
        SUCCESS,
        ERROR_CONVERSION,
        FAIL_GAME_RUN = -1,
        game_lost
    };

    //this struct is trying to mimic a class
    //by breaking a lot of incapsulation rules
    struct GameWorld
    {
        int intRows;
        int intCols;
        int intPR;
        int intPC;
        int remaining;
        int points;
        GameArray aryWorld;

        //pointers to function
        /*this will help me have some sort of functionality
        the pointers do not perfom any functions they just point to methods that will perform those function*/
        void (*showWorld)(GameWorld recWorld);
        void (*movePlayer)(GameWorld& recWorld, Direction eDir);
        void (*freeWorld)(GameWorld& recWorld);
    };

    GameWorld makeWorld(int intRows, int intCols);
}
#endif
