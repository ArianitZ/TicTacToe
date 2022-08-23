#include "SDL2/SDL.h"
#include <string>

class Window
{
    public:
        Window(int width, int height, std::string title);

        bool init();
        void render();
        void free();

        int getWidth();
        int getHeight();
        std::string getTitle();

    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        std::string mTitle;

        int mWidth;
        int mHeight;
};


Window::Window(int width, int height, std::string title)
{
    mWindow = NULL;
    mRenderer = NULL;

    mTitle = title;

    mWidth = width;
    mHeight = height;
}

bool Window::init()
{
    mWindow = SDL_CreateWindow(mTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
        printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (mRenderer == NULL)
    {
        printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
        // TODO: call free() to destroy Window if renderer is not successfully created?
        return false;
    }

    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

void Window::render()
{
    if(mRenderer!=NULL)
    {
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);
    }
}

void Window::free()
{
    if(mWindow != NULL)
    {
        SDL_DestroyWindow(mWindow);
        mWindow = NULL;
    }
    
    if(mRenderer != NULL)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = NULL;
    }
}

int Window::getHeight()
{
    return mHeight;
}

int Window::getWidth()
{
    return mWidth;
}

std::string Window::getTitle()
 {
     return mTitle;
 }


// Initializes SDL
bool init();

// Deallocates and closes relevant variables & systems
void close();


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