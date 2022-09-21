#include "player.h"

Point::Point(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Point::getX()
{
    return m_x;
}

int Point::getY()
{
    return m_y;
}


Player::Player(Texture texture, std::string marker_type)
{
    m_texture = texture;
    m_marker_type = marker_type;
}

void Player::render(SDL_Renderer* renderer)
{
    for(int i{0}; i < m_positions.size(); ++i)
    {
        m_texture.render(m_positions[i].getX(), m_positions[i].getY(), renderer);
    }
}

void Player::addPosition(int x, int y)
{
    Point new_position = Point(x,y);
    m_positions.push_back(new_position);
}

std::vector<Point> Player::getPositions()
{
    return (m_positions);
}

Texture* Player::getTexture()
{
    return (&m_texture);
}

std::string Player::getMarkerType()
{
    return m_marker_type;
}