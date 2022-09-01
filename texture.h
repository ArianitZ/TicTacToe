#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
    public:
        Texture();

        bool loadFromFile(std::string path, SDL_Renderer* renderer);

        void free();
        void render(int x, int y, SDL_Renderer* renderer);
    
    private:
        SDL_Texture* mTexture;

        int mHeight;
        int mWidth;
};
#endif