#include "texture.h"

Texture::Texture()
{
    mTexture = NULL;

    mHeight = 0;
    mWidth = 0;
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    // Get rid of pre-existing texture
    free();

    SDL_Surface* tmp_surface = IMG_Load(path.c_str());
    if(tmp_surface == NULL)
    {
        printf("Could not load image, IMG error: %s\n", IMG_GetError());
        return false;
    }

    // Color key image. Make white pixels transparent.
    SDL_SetColorKey(tmp_surface, SDL_TRUE, SDL_MapRGB(tmp_surface->format, 0xFF, 0xFF, 0xFF));
    mTexture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    if(mTexture == NULL)
    {
        SDL_FreeSurface(tmp_surface);
        printf("Could not create texture from surface! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    mHeight = tmp_surface->h;
    mWidth = tmp_surface->w;

    SDL_FreeSurface(tmp_surface);

    return true;
}

void Texture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mHeight = 0;
        mWidth = 0;
    }
}

void Texture::render(int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect render_rectangle = {x, y, mWidth, mHeight};

    SDL_RenderCopyEx(renderer, mTexture, NULL, &render_rectangle, 0.0, NULL, SDL_FLIP_NONE);
}