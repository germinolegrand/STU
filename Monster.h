#ifndef MONSTER_H
#define MONSTER_H

#include "using.h"

class Monster
{
public:
    Monster(sf::Texture &texture);
    virtual ~Monster();

private:
    sf::Sprite m_sprite;

friend void draw(Renderer &ren, const Monster &monster);
};

void draw(Renderer &ren, const Monster &monster);

#endif // MONSTER_H
