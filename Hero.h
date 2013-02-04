#ifndef HERO_H
#define HERO_H

#include "using.h"

class Hero
{
public:
    Hero(const std::string &filename);
    virtual ~Hero();

    void move(const sf::Vector2f &offset);
private:
    sf::Texture m_spritesSheet;
    sf::Sprite m_skin;

    sf::Vector2f m_position;

friend void draw(Renderer &ren, const Hero &hero);
};

void draw(Renderer &ren, const Hero &hero);

#endif // HERO_H
