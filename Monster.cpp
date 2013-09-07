#include "Monster.h"

Monster::Monster(sf::Texture &texture):
    m_sprite(texture)
{
    //ctor
}

Monster::~Monster()
{
    //dtor
}

void draw(Renderer& ren, const Monster& monster)
{
    ren.draw(monster.m_sprite);
}
