#include "Life.h"

Life::Life(int life):
    m_life(life)
{
    //ctor
}

void draw(Renderer &ren, const Life &life, const sf::Vector2f& position)
{
    sf::RectangleShape rectsh({4.f, 4.f});
    rectsh.setPosition(position);
    rectsh.setFillColor(sf::Color::Red);

    for(int i = 0; i < life.m_life; ++i)
    {
        draw(ren, rectsh);

        rectsh.move({5.f, 0.f});
    }
}

bool isAlive(const Life& life)
{
    return life.m_life > 0;
}
