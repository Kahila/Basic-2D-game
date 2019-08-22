#include <cstdlib>
#include <ctime>
#include <iostream>
#include "fact.h"

using namespace std;
using namespace FactorySpace;

int main(int argc, char **argv)
{
    //the game will only play if the arguments are three;
    cout << "arg 1 -> rows\narg 2 -> columns" << endl;
    if (argc == 3)
    {
        srand(time(nullptr));
        //the rows and columns will be used to create the game;
        //the recworld is my sudo object;
        GameWorld recWorld = makeWorld(atoi(argv[1]), atoi(argv[2]));
        recWorld.remaining = 0;
        recWorld.points = 10;
        bool blnContinue = true;

        do//the do loop will run atleast once
        {
            system("cls");
            recWorld.showWorld(recWorld);
            cout << "\ncollected parts  > " << recWorld.remaining << endl;//shows the number of parts collected
            cout << "lives  > " << recWorld.points << endl; //shows the lives remaining
            cout << "|| if you go to the factory empty handed you will lose 10 points ||" << endl;
            cout << "w) Up a) Left s) Down d) Right x) Exit " << endl
                << "Selection: ";
            char chSelection = '\0';
            cin >> chSelection;

            switch(chSelection)
            {
                case 'w':
                case 'W':
                    recWorld.movePlayer(recWorld, UP);//move up
                    break;

                case 's':
                case 'S':
                    recWorld.movePlayer(recWorld, DOWN);//move down
                    break;

                case 'a':
                case 'A':
                    recWorld.movePlayer(recWorld, LEFT); //move left
                    break;

                case 'd':
                case 'D':
                    recWorld.movePlayer(recWorld, RIGHT);//move right
                    break;

                case 'x':
                case 'X':
                    blnContinue = false;//exit game
                    break;

                case 'q':
                case 'Q':
                    recWorld.movePlayer(recWorld, NW); //move north west
                    break;

                case 'e':
                case 'E':
                    recWorld.movePlayer(recWorld, NE);//mmove north east
                    break;

                case 'z':
                case 'Z':
                    recWorld.movePlayer(recWorld, SW);//move South west
                    break;

                case 'C':
                case 'c':
                    recWorld.movePlayer(recWorld, SE);//move South east
                    break;

                default:
                    cerr << chSelection << "Invalid" << endl;
                    system("pause");
            }
        } while(blnContinue);// will keep running as long as the plauer has not pressed x
        recWorld.freeWorld(recWorld);
        return (SUCCESS);
    }
    cout << "\n\nTHERE MUST BE 3 ARGUMENTS" << endl;
    return (FAIL_GAME_RUN);
    }
