#include "Game_engine.h"
#include <Windows.h>
#include <time.h>

int main() 
{
    //Starting game
    srand(time(NULL));
    Game_engine game;

    //Game loop
    while (game.running())
    {
        //Updating window to draw new grame later
        game.updateWindow(); 

        //Drawing new frame (moment of milions during the process)
        game.renderWindow();
    }

    //Ending game
    return 0;
}