#ifndef HERO_H
#define HERO_H

#include "using.h"

#include "HeroCollider.h"

class Hero
{
public:
    Hero(const std::string &filename);
    virtual ~Hero();

    void move(const sf::Vector2f &offset);

    void setPosition(const sf::Vector2f &uncheckedPosition);
private:
    sf::Texture m_spritesSheet;
    sf::Sprite m_skin;

    sf::Vector2f m_position;

    HeroCollider m_collider {{5.f,16.f, 14.f, 19.f}};

friend void draw(Renderer &ren, const Hero &hero);
};

void draw(Renderer &ren, const Hero &hero);

#endif // HERO_H
