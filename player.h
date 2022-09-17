#ifndef PLAYER_H
#define PLAYER_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <vector>
#include <string>

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
        Player(Texture texture, std::string marker_type);

        void render(SDL_Renderer* renderer);

        void addPosition(int x, int y);
    
        std::vector<Point>* getPositions();

        Texture* getTexture();
        
        std::string getMarkerType();

    private:
        Texture mTexture;
        std::string m_marker_type;
        std::vector<Point> mPositions;

};

#endif