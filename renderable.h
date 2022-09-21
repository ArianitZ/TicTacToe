#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL2/SDL.h>
class IRenderable
{
    public:
        virtual void render(SDL_Renderer* renderer) = 0;

        virtual ~IRenderable() {}
};

#endif