#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include <SDL2/SDL.h>

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

#endif