#ifndef PLAYER_H
#define PLAYER_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <vector>

class Point
{   
    public:
        Point(int x, int y);

        int getX();
        int getY();

    private:
        int mX{};
        int mY{};

};

class Player
{
    public:
        Player(Texture texture);

        void render(SDL_Renderer* renderer);

        void addPosition(int x, int y);
    
        std::vector<Point>* getPositions();

        Texture* getTexture();
        

    private:
        Texture mTexture;
        std::vector<Point> mPositions;

};

#endif