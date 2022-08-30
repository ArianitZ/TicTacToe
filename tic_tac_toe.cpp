#include "window.h"

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
    }

    return success;
}

void close(Window* window)
{
    printf("Closing down game!\n");
    window->free();
    SDL_Quit();
} 

int main(int argc, char* argv[])
{    
    int screen_height = 400;
    int screen_width = 600;
    std::string window_title = "Tic Tac Toe";
    Window window = Window(screen_width, screen_height, window_title);

    if(init(&window))
    {   
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

            window.render();
        }
    }
    close(&window);
    return 0;
}