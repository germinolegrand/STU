#include "Hero.h"

#include <iostream>

Hero::Hero(const std::string &filename)
{
    sf::Image img;
    img.loadFromFile(filename);
    img.createMaskFromColor(sf::Color::Magenta, 0);
    m_spritesSheet.loadFromImage(img);

    m_skin.setTexture(m_spritesSheet);
    //m_skin.setOrigin(17.5f, 28.5f);
}

Hero::~Hero()
{
    //dtor
}

void Hero::move(const sf::Vector2f& offset)
{
    auto position = m_collider.onMove(*this, m_position + offset);
    m_position = position;
    m_skin.setPosition(position);
}



void draw(Renderer &ren, const Hero &hero)
{
    draw(ren, hero.m_skin);
    draw(ren, hero.m_collider, hero.m_position);
}
