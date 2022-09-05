#ifndef PLAYER_H
#define PLAYER_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <vector>

struct Point
{
    int x{};
    int y{};
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