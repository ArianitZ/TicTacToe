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


Player::Player(Texture texture)
{
    mTexture = texture;
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