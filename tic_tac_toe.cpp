#include "texture.h"
#include "player.h"
#include "game.h"


int main(int argc, char* argv[])
{    
    int screen_height = 194; // 64 * 3 + 2. Each cell is 64x64 and we have two lines separating cells.
    int screen_width = 194;
    Game game = Game(screen_height, screen_width);

    if(game.init())
    {   
        game.load_media();
        game.assign_textures();

        // Main loop
        while(!game.game_over())
        {
            game.handle_events();
            game.render_all();
        }
    }
    game.close();
    return 0;
}