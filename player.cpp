#include "player.h"

Point::Point(int x, int y)
{
    mX = x;
    mY = y;
}

int Point::getX()
{
    return mX;
}

int Point::getY()
{
    return mY;
}


Player::Player(Texture texture, std::string marker_type)
{
    mTexture = texture;
    m_marker_type = marker_type;
}

void Player::render(SDL_Renderer* renderer)
{
    for(int i{0}; i < mPositions.size(); ++i)
    {
        mTexture.render(mPositions[i].getX(), mPositions[i].getY(), renderer);
    }
}


void Player::addPosition(int x, int y)
{
    Point new_position = Point(x,y);
    mPositions.push_back(new_position);
}

std::vector<Point>* Player::getPositions()
{
    return (&mPositions);
}

Texture* Player::getTexture()
{
    return (&mTexture);
}

std::string Player::getMarkerType()
{
    return m_marker_type;
}