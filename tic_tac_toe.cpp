#include "texture.h"
#include "player.h"
#include "game.h"


int main(int argc, char* argv[])
{    
    int screen_height = 193;
    int screen_width = 193;
    Game game = Game(screen_height, screen_width);

    if(game.init())
    {   
        game.loadMedia();
        game.assignTextures();

        // Main loop
        while(!game.gameOver())
        {
            game.handleEvents();
            game.render();
        }
    }
    game.close();
    return 0;
}