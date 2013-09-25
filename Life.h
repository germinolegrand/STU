#ifndef LIFE_H
#define LIFE_H

#include "using.h"

class Life
{
public:
    Life(int life);

    Life& operator+=(int add){ m_life += add; return *this; };
    Life& operator-=(int sub){ m_life -= sub; return *this; };

private:
    int m_life;

friend void draw(Renderer &ren, const Life &life, const sf::Vector2f& position);
friend bool isAlive(const Life& life);
};

#endif // LIFE_H
