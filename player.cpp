#include "player.h"

Player::Player(Texture texture)
{
    mTexture = texture;
}

void Player::render(SDL_Renderer* renderer)
{
    for(int i{0}; i < mPositions.size(); ++i)
    {
        mTexture.render(mPositions[i].x, mPositions[i].y, renderer);
    }
}


void Player::addPosition(int x, int y)
{
    Point new_position = {x,y};
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