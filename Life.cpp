#include "Life.h"

#include <iostream>

Life::Life(int life):
    m_life(life)
{
    //ctor
}

void draw(Renderer &ren, const Life &life, const sf::Vector2f& position)
{
    sf::RectangleShape rectsh({4.f, 4.f});
    rectsh.setPosition(position);
    rectsh.setFillColor(life.m_life >= 1000 ? sf::Color::Magenta
                       : life.m_life >= 100 ? sf::Color::Blue
                        : life.m_life >= 10 ? sf::Color::Green
                                            : sf::Color::Red);
    int life_10 = life.m_life;
    while(life_10 >= 10)
        life_10/=10;

    for(int i = 0; i < life_10; ++i)
    {
        draw(ren, rectsh);

        rectsh.move({5.f, 0.f});
    }
}

bool isAlive(const Life& life)
{
    return life.m_life > 0;
}
