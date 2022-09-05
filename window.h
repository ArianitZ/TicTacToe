#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "player.h"

class Window
{
    public:
        Window(int width, int height, std::string title);

        bool init();
        void render(std::vector<Player> players);
        void free();

        SDL_Renderer* getRenderer();
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

#endif