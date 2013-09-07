#ifndef HERO_H
#define HERO_H

#include "using.h"

#include "TextureManager.h"
#include "HeroCollider.h"

class Hero
{
public:
    Hero(TextureManager textures);
    virtual ~Hero();

    void move(const sf::Vector2f &offset);

    void setPosition(const sf::Vector2f &uncheckedPosition);
private:
    TextureManager m_textures;

    sf::Sprite m_skin;

    sf::Vector2f m_position;

    HeroCollider m_collider {{5.f,16.f, 14.f, 19.f}};

friend void draw(Renderer &ren, const Hero &hero);
};

void draw(Renderer &ren, const Hero &hero);

#endif // HERO_H
