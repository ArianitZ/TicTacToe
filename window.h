#ifndef WINDOW_H
#define WINDOW_H
#include <vector>
#include <SDL2/SDL.h>
#include "renderable.h"
#include "texture.h"

class Window
{
    public:
        Window(int width, int height, std::string title);

        bool init();
        void render_clear();
        void render(std::vector<IRenderable*> rendering_objects);
        void render_present();
        void render_single_object(Texture* texture_object, int x, int y);
        void free();

        SDL_Renderer* getRenderer();
        int getWidth();
        int getHeight();
        std::string getTitle();

    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;

        int mWidth;
        int mHeight;

        std::string mTitle;
};

#endif