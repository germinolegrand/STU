#include "Hero.h"

#include <iostream>

Hero::Hero(TextureManager textures):
    m_textures(textures)
{
    m_skin.setTexture(m_textures["heros_bidon"]);
    //m_skin.setOrigin(17.5f, 28.5f);
}

void Hero::move(const sf::Vector2f& offset)
{
    auto position = m_collider.onMove(*this, m_position + offset);
    m_position = position;
    m_skin.setPosition(position);
}

void Hero::setPosition(const sf::Vector2f& uncheckedPosition)
{
    m_position = uncheckedPosition;
}


void draw(Renderer &ren, const Hero &hero)
{
    draw(ren, hero.m_skin);
    draw(ren, hero.m_collider, hero.m_position);
    draw(ren, hero.m_life, sf::Vector2f(hero.m_skin.getGlobalBounds().left, hero.m_skin.getGlobalBounds().top + hero.m_skin.getLocalBounds().height));
}

sf::FloatRect getCollisionBox(const Hero& h)
{
    auto collide_box = getCollisionBox(h.m_collider);
    collide_box.left += h.m_position.x;
    collide_box.top += h.m_position.y;

    return collide_box;
}

sf::Vector2f getBulletCreationPoint(const Hero& h)
{
    auto BBox = h.m_skin.getGlobalBounds();
    return {BBox.left + BBox.width/2, BBox.top};
}

void takeDamages(Hero& h, int damages)
{
    h.m_life -= damages;
}

bool isAlive(const Hero& h)
{
    return isAlive(h.m_life);
}
