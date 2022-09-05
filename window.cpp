#include "window.h"

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

void Window::render(std::vector<Player> players)
{
    if(mRenderer!=NULL)
    {
        SDL_RenderClear(mRenderer);
        for(int i{0}; i < players.size(); ++i)
        {
            players[i].render(mRenderer);
        }
        SDL_RenderPresent(mRenderer);
    }
    else
    {
        printf("Renderer has not been initialized, cannot render!");
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

SDL_Renderer* Window::getRenderer()
{
    return mRenderer;
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