#include "window.h"
#include "texture.h"
#include "player.h"

// Initializes SDL
bool init(Window* window);

// Deallocates and closes relevant variables & systems
void close();

// Loads media
void loadMedia();


bool init(Window* window)
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if(!window->init())
        {
            success = false;
        }
        // Initialize SDL_image
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if(!IMG_Init(imgFlags))
            {
                printf("Unable to initialize SDL_image! SDL_image Error: %s\n", IMG_GetError());
            }
        }
    }

    return success;
}

void close(Window* window)
{
    printf("Closing down game!\n");
    window->free();

    SDL_Quit();
    IMG_Quit();
} 

int main(int argc, char* argv[])
{    
    int screen_height = 193;
    int screen_width = 193;
    std::string window_title = "Tic Tac Toe";
    Window window = Window(screen_width, screen_height, window_title);

    if(init(&window))
    {   
        Texture x_texture = Texture();
        Texture o_texture = Texture();

        x_texture.loadFromFile("assets/x.png", window.getRenderer());
        o_texture.loadFromFile("assets/o.png", window.getRenderer());
        
        // TODO Assign randomly x/o textures to players
        std::vector<Player> players = {Player(x_texture), Player(o_texture)};
        players[0].addPosition(0,0);
        bool quit = false;

        SDL_Event event;
        // Main loop
        while(!quit)
        {
            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_QUIT)
                {   
                    quit = true;
                }
            }

            window.render(players);
        }
    }
    close(&window);
    return 0;
}