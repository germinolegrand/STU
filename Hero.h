#ifndef HERO_H
#define HERO_H

#include "using.h"

#include "TextureManager.h"
#include "HeroCollider.h"
#include "Life.h"

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

    Life m_life {10};

friend void draw(Renderer &ren, const Hero &hero);
friend sf::FloatRect getCollisionBox(const Hero& h);
friend sf::Vector2f getBulletCreationPoint(const Hero& h);
friend void takeDamages(Hero& h, int damages);
friend bool isAlive(const Hero& h);
};

#endif // HERO_H
