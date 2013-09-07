#include "Hero.h"

#include <iostream>

Hero::Hero(TextureManager textures):
    m_textures(textures)
{
    m_skin.setTexture(m_textures["heros_bidon"]);
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
