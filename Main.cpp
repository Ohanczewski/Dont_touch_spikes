#include "Game_engine.h"

int main() 
{
    //Starting game
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