#ifndef PLAYER_H
#define PLAYER_H
#include "texture.h"
#include "renderable.h"
#include <vector>

class Point
{   
    public:
        Point(int x, int y);

        int getX();
        int getY();

    private:
        int m_x{};
        int m_y{};

};

class Player : public IRenderable
{
    public:
        Player(Texture texture, std::string marker_type);

        void render(SDL_Renderer* renderer);

        void addPosition(int x, int y);
    
        std::vector<Point> getPositions();

        Texture* getTexture();
        
        std::string getMarkerType();

    private:
        Texture m_texture;
        std::string m_marker_type;
        std::vector<Point> m_positions;

};

#endif