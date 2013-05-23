#ifndef HEROCOLLIDER_H
#define HEROCOLLIDER_H

#include "using.h"

class Hero;

class HeroCollider
{
public:
    HeroCollider(const sf::FloatRect &box);
    virtual ~HeroCollider();

    const sf::Vector2f& onMove(Hero &he, const sf::Vector2f &pos);

private:
    sf::FloatRect m_box;

friend void draw(Renderer &ren, const HeroCollider& coll, const sf::Vector2f& hero_position);
};

void draw(Renderer &ren, const HeroCollider& coll, const sf::Vector2f& hero_position);

#endif // HEROCOLLIDER_H
